import memory;
import mizu;
import hook;
import util;

#include "../include.h"
#include "nt.h"
#include "virtual.h"
#include "../sdk/sdk.h"

std::vector<std::byte> Memory::ParsePattern(const std::string& pattern) {
	std::vector<std::byte> patternBytes;

	for (size_t i = 0; i < pattern.size(); i++) {
		if (pattern[i] == wildcard) {
			patternBytes.push_back(std::byte(0));

			if (i + 1 < pattern.size() && pattern[i + 1] == wildcard)
				i++;

			continue;
		}

		if (pattern[i] == ' ')
			continue;

		if (i + 1 >= pattern.size())
			return std::vector<std::byte>();

		std::string byteString = pattern.substr(i, 2);
		patternBytes.push_back(std::byte(std::stoi(byteString, nullptr, 16)));
		i++;
	}

	return patternBytes;
}

Memory::Binary_t Memory::GetModule(const std::wstring& name)
{
	if (!m_peb)
		return {};

	const NT::ListEntry_t head = m_peb->Ldr->InMemoryOrderModuleList;
	for (NT::ListEntry_t current = head; current.Flink != &m_peb->Ldr->InMemoryOrderModuleList; current = *current.Flink) {
		const NT::LdrDataTableEntry_t* data = (const NT::LdrDataTableEntry_t*)CONTAINING_RECORD(current.Flink, NT::LdrDataTableEntry_t, InMemoryOrderLinks);
		if (data->BaseDllName.Buffer) {
			if (_wcsicmp(data->BaseDllName.Buffer, name.c_str()) == 0) {
				Util::Log<LOG_DEBUG>("found module: {}", std::string(name.begin(), name.end()).c_str());
				return Binary_t(data->DllBase);
			}
		}
	}

	Util::Log<LOG_ERROR>("failed to find module: {}", std::string(name.begin(), name.end()).c_str());
	return {};
}

Memory::Binary_t::Binary_t(const void* mod) {
	Util::Log<LOG_DEBUG>("module: {}", (void*)mod);
	m_dosHeaders = (NT::ImageDosHeader_t*)mod;
	m_ntHeaders = (NT::ImageNtHeaders_t*)((DWORD_PTR)mod + m_dosHeaders->e_lfanew);
	m_dataDirectory = (NT::ImageDataDirectory_t*)m_ntHeaders->OptionalHeader.DataDirectory;
	m_exportDirectory = (NT::ImageExportDirectory_t*)((DWORD_PTR)mod + m_dataDirectory->VirtualAddress);

	Util::Log<LOG_DEBUG>("module size: {:X}", m_ntHeaders->OptionalHeader.SizeOfImage);
	m_moduleSpan = std::span<const std::byte>((const std::byte*)mod, m_ntHeaders->OptionalHeader.SizeOfImage);

	auto rvaTable = (const uint32_t*)((DWORD_PTR)mod + m_exportDirectory->AddressOfFunctions);
	auto rvaNames = (const DWORD*)((DWORD_PTR)mod + m_exportDirectory->AddressOfNames);
	auto ordTable = (const WORD*)((DWORD_PTR)mod + m_exportDirectory->AddressOfNameOrdinals);

	if (m_exportDirectory) {
		m_exports.reserve(m_exportDirectory->NumberOfNames);
		Util::Log<LOG_DEBUG>("{} exports found", m_exportDirectory->NumberOfNames);

		for (unsigned long i = 0; i < m_exportDirectory->NumberOfNames; i++) {
			const std::string name = (const char*)((DWORD_PTR)mod + rvaNames[i]);
			const uintptr_t addr = (const uintptr_t)((DWORD_PTR)mod + rvaTable[ordTable[i]]);
			m_exports[name] = addr;
		}
	}

	NT::ImageSectionHeader_t* section = (NT::ImageSectionHeader_t*)IMAGE_FIRST_SECTION(m_ntHeaders);
	Util::Log<LOG_DEBUG>("{} sections found", m_ntHeaders->FileHeader.NumberOfSections);
	m_sections.reserve(m_ntHeaders->FileHeader.NumberOfSections);
	for (unsigned long i = 0; i < m_ntHeaders->FileHeader.NumberOfSections; i++) {
		m_sections.push_back(section[i]);
	}
}

Memory::Cursor_t& Memory::Cursor_t::SetSearchDirection(bool forward) {
	bool backwards = m_flags & Backward;
	if (backwards && forward)
		m_flags &= ~Backward;
	else if (forward && !backwards)
		m_flags |= Backward;
	return *this;
}

Memory::Cursor_t& Memory::Cursor_t::SetMatchCount(std::uint16_t match) {
	m_matchCount = match;
	return *this;
}

Memory::MemSearchError_t Memory::Cursor_t::FindPattern(const std::string& pattern) {
	std::vector<std::byte> patternBytes = ParsePattern(pattern);

	if (patternBytes.empty())
		return MemSearchError_t::InvalidPattern;

	uint16_t matchCount = 0;
	size_t searchSize = m_span.size() - patternBytes.size();

	if (m_flags & Backward) {
		for (size_t i = searchSize - 1; i > 0; i--) {
			if (m_span[i] == patternBytes[0]) {
				bool found = true;

				for (size_t j = 1; j < patternBytes.size(); j++) {
					if (patternBytes[j] != std::byte(0) && m_span[i + j] != patternBytes[j]) {
						found = false;
						break;
					}
				}

				if (found) {
					if (++matchCount == m_matchCount) {
						m_address = (uintptr_t)(m_span.data() + i);
						return MemSearchError_t::OK;
					}
				}
			}
		}
	}
	else {
		for (size_t i = 0; i < searchSize; i++) {
			if (m_span[i] == patternBytes[0]) {
				bool found = true;

				for (size_t j = 1; j < patternBytes.size(); j++) {
					if (patternBytes[j] != std::byte(0) && m_span[i + j] != patternBytes[j]) {
						found = false;
						break;
					}
				}

				if (found) {
					if (++matchCount == m_matchCount) {
						m_address = (uintptr_t)(m_span.data() + i);
						return MemSearchError_t::OK;
					}
				}
			}
		}
	}

	return MemSearchError_t::NoMatch;
}

Memory::MemSearchError_t Memory::Cursor_t::FindString(const std::string_view string) {
	std::vector<std::byte> patternBytes = std::vector<std::byte>((const std::byte*)string.data(), (const std::byte*)(string.data() + string.size()));

	if (patternBytes.empty())
		return MemSearchError_t::InvalidPattern;

	uint16_t matchCount = 0;
	size_t searchSize = m_span.size() - patternBytes.size();

	if (m_flags & Backward) {
		for (size_t i = searchSize - 1; i > 0; i--) {
			if (m_span[i] == patternBytes[0]) {
				bool found = true;

				for (size_t j = 1; j < patternBytes.size(); j++) {
					if (patternBytes[j] != std::byte(0) && m_span[i + j] != patternBytes[j]) {
						found = false;
						break;
					}
				}

				if (found) {
					if (++matchCount == m_matchCount) {
						m_address = (uintptr_t)(m_span.data() + i);
						return MemSearchError_t::OK;
					}
				}
			}
		}
	}
	else {
		for (size_t i = 0; i < searchSize; i++) {
			if (m_span[i] == patternBytes[0]) {
				bool found = true;

				for (size_t j = 1; j < patternBytes.size(); j++) {
					if (patternBytes[j] != std::byte(0) && m_span[i + j] != patternBytes[j]) {
						found = false;
						break;
					}
				}

				if (found) {
					if (++matchCount == m_matchCount) {
						m_address = (uintptr_t)(m_span.data() + i);
						return MemSearchError_t::OK;
					}
				}
			}
		}
	}

	return MemSearchError_t::NoMatch;
}

Memory::Cursor_t Memory::Binary_t::FindPattern(const std::string& pattern, std::uint32_t flags, size_t offset, size_t size) {
	Cursor_t cursor = Cursor_t(size == 0 ? m_moduleSpan : m_moduleSpan.subspan(offset, size));
	//cursor.SetSearchDirection(!(flags & CursorFlags_t::Backward));
	// cursor.SetMatchCount(1);
	cursor.m_flags = flags;
	cursor.m_error = cursor.FindPattern(pattern);

	return cursor;
}

bool Memory::Binary_t::WipeHeaders() const
{
	//

	return true;
}

bool Memory::Addresses::Setup() {
	m_clientState = m_bin.FindPattern(_("48 8D 0D ? ? ? ? E9 ? ? ? ? C3 CC 48 8B CA")).RelJmp().Cast();
	if (!m_clientState.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find clientState"));
		return false;
	}

	m_cl_entity_list = m_bin.FindPattern(_("48 8D 05 ? ? ? ? 44 2B")).RelJmp().Cast();
	if (!m_cl_entity_list.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find cl_entity_list"));
		return false;
	}

	m_chlClient = m_bin.FindPattern(_("48 8D 0D ? ? ? ? FF 90 ? ? ? ? 8B 45 10")).RelJmp().Cast();
	if (!m_chlClient.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find chlclient"));
		return false;
	}

	m_engineClient = m_bin.FindPattern(_("48 8D 0D ? ? ? ? FF 90 ? ? ? ? 84 C0 75 74")).RelJmp().Cast();
	if (!m_engineClient.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find engineClient"));
		return false;
	}

	m_input = m_bin.FindPattern(_("48 8D 0D ? ? ? ? 33 D2 48 83 C4 20")).RelJmp().Cast();
	if (!m_input.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find input"));
		return false;
	}

	m_gameMovement = m_bin.FindPattern(_("48 89 05 ? ? ? ? 48 83 C4 28 C3 CC CC 48 83 EC 28 48 8B 15")).RelJmp().Cast();
	if (!m_gameMovement.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find gameMovement"));
		return false;
	}

	m_globalVars = m_bin.FindPattern(_("48 8D 15 ? ? ? ? FF 50 18 85 C0")).RelJmp().Cast();
	if (!m_globalVars.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find globalVars"));
		return false;
	}

	m_viewRender = m_bin.FindPattern(_("48 8B 0D ? ? ? ? 33 D2 48 8B 01 FF 90 ? ? ? ? F3 0F 10 00")).RelJmp().Cast();
	if (!m_viewRender.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find viewRender"));
		return false;
	}

	m_localPlayerPtr = m_gameMovement.Offset(sizeof(uintptr_t));
	if (!m_localPlayerPtr.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find localPlayerPtr"));
		return false;
	}

	m_levelName = m_bin.FindPattern(_("48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC 83 3D")).RelJmp().Cast();
	if (!m_levelName.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find levelName"));
		return false;
	}

	m_modelPtr = m_bin.FindPattern(_("48 83 B9 ? ? ? ? ? 75 18")).Cast();
	if (!m_modelPtr.Valid()) {
		Util::Log<LOG_ERROR>(_("failed to find model ptr"));
		return false;
	}

	return true;
}

bool Memory::Setup(HMODULE _module) {
	Util::consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	m_module = _module;
	m_peb = (NT::PEB*)__readgsqword(0x60);
	if (!m_peb)
		return false;

	m_base = Address_t(m_peb).Offset(0x10).Get();

	m_bin = Binary_t(m_base.Cast<HMODULE>());
	if (!m_bin.IsValid())
		return false;

	Util::Log(_("kernel32"));
	m_kernel32 = GetModule(_(L"Kernel32.dll"));
	if (!m_kernel32.IsValid())
		return false;

	Util::Log(_("hello {}"), _("dev"));

	if (!Addresses::Setup())
		return false;

	if (m_dxgi.m_exports.find(_("D3D11CreateDeviceAndSwapChain")) == m_d3d11.m_exports.end()) {
		Util::Log<LOG_ERROR>(_("failed to find D3D11CreateDeviceAndSwapChain"));
		return false;
	}

	Util::Log(_("base: {:X}, size: {:X}"), m_base.m_address, m_bin.m_moduleSpan.size());

	Util::Log("memory::setup done!\n");
	return true;
}