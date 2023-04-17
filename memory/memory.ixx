module;

#include "../include.h"
#include "nt.h"

#include <TlHelp32.h>
#include <Psapi.h>

export module memory;

export namespace Memory {
	inline constexpr char wildcard = '?';

	enum class MemSearchError_t {
		OK,
		InvalidModule,
		InvalidPattern,
		InvalidSpan,
		InvalidSize,
		NoMatch,
		OutOfBounds
	};

	enum CursorFlags_t {
		None = 0 << 0,
		// Goes from end to start, if this isn't set it goes from start to end.
		Backward = 1 << 0,
	};

	struct Address_t {
		Address_t() = default;

		template <typename T> Address_t(const T _address) noexcept {
			m_address = (uintptr_t)_address;
		}

		bool operator==(const Address_t& pointer) const noexcept {
			return m_address == pointer.Cast<uintptr_t>();
		}

		bool operator!=(const Address_t& pointer) const noexcept {
			return m_address != pointer.Cast();
		}

		template <typename T = Address_t> T Cast() const noexcept {
			return m_address ? (T)m_address : T();
		}

		template <typename T = Address_t> T& Get() noexcept {
			return *(T*)m_address;
		}

		template <typename T = Address_t> T Offset(std::ptrdiff_t offset = 0x1) noexcept {
			return m_address ? (T)(m_address + offset) : T();
		}

		template <typename T = Address_t> inline T Deref(unsigned int dereferences = 1u) noexcept {
			if (!Valid())
				return T();

			uintptr_t curAddress = m_address;

			while (dereferences--)
				if (curAddress)
					curAddress = *(uintptr_t*)curAddress;

			return (T)curAddress;
		}

		// to get a variable after instruction
		template <typename T = Address_t> T RelJmp(size_t instructionSize = 0x3) noexcept {
			if (!Valid())
				return T();

			long relOffset = *(long*)((uintptr_t)m_address + instructionSize);
			uintptr_t pastInstruction = (uintptr_t)m_address + instructionSize + sizeof(long);
			return (T)(pastInstruction + relOffset);
		}

		// to get an offset after instruction
		long RelativeOffset(size_t instructionSize = 0x3) noexcept {
			if (!Valid())
				return 0;

			return *(long*)(m_address + instructionSize);
		}

		bool Valid() const {
			return m_address != 0u;
		}

		uintptr_t m_address = 0u;
	};

	// This class will iterate memory and handle all of the memory arithmetic, use of a builder instead of a constructor for more flexibility
	struct Cursor_t : Address_t {
		Cursor_t() = delete;
		Cursor_t(const std::span<const std::byte> span) : m_span(span), Address_t((uintptr_t)span.data()) {}

		// Builder fields
		Cursor_t& SetSpan(std::span<const std::byte>& span) { m_span = span; return *this; }
		Cursor_t& SetSearchDirection(bool forward);
		Cursor_t& SetMatchCount(uint16_t match);
		Cursor_t& Reset() { m_address = (uintptr_t)m_span.data(); return *this; }
		Cursor_t& Offset(ptrdiff_t offset) { m_address += offset; return *this; }
		long RelativeOffset(size_t instructionSize) {
			return *(long*)((uintptr_t)m_address + instructionSize);
		}
		Cursor_t& RelJmp(size_t instructionSize = 0x3) {
			long relOffset = *(long*)((uintptr_t)m_address + instructionSize);
			uintptr_t pastInstruction = (uintptr_t)m_address + instructionSize + sizeof(long);
			m_address = (uintptr_t)(pastInstruction + relOffset);
			return *this;
		}
		bool Valid() const { return m_address != 0u && m_error == MemSearchError_t::OK; }

		// Finds the first occurence of the pattern in the span
		MemSearchError_t FindPattern(const std::string& pattern);
		MemSearchError_t FindString(const std::string_view string);

		std::span<const std::byte> m_span;
		std::uint32_t m_flags = CursorFlags_t::None;
		std::uint16_t m_matchCount = 1;
		MemSearchError_t m_error = MemSearchError_t::OK;
	};

	struct Binary_t {
		Binary_t() = default;
		Binary_t(const void* mod);

		// Initiate a search
		Cursor_t Find(size_t offset, size_t size = 0) {
			return Cursor_t(m_moduleSpan.subspan(offset, size == 0 ? m_moduleSpan.size() - offset : size));
		}
		Cursor_t FindPattern(const std::string& pattern, std::uint32_t flags = CursorFlags_t::None, size_t offset = 0, size_t size = 0);

		bool IsValid() const {
			return !m_moduleSpan.empty();
		}
		bool IsValid(uintptr_t addr) const {
			return addr >= (uintptr_t)m_moduleSpan.data() && addr < (uintptr_t)m_moduleSpan.data() + m_moduleSpan.size() && addr != 0;
		}
		bool HasCharacteristics(uintptr_t addr, uint32_t characteristics) const {
			if (!IsValid(addr))
				return false;

			for (const auto& section : m_sections) {
				if (!(section.Characteristics & characteristics))
					continue;

				const uintptr_t start = (uintptr_t)m_moduleSpan.data() + section.VirtualAddress;
				const uintptr_t end = start + section.Misc.VirtualSize;
				if (addr >= start && addr < end)
					return true;
			}

			return false;
		}
		bool InExecutableMemory(uintptr_t addr) const {
			return HasCharacteristics(addr, IMAGE_SCN_MEM_EXECUTE);
		}
		bool WipeHeaders() const;

		NT::ImageDosHeader_t* m_dosHeaders = nullptr;
		NT::ImageNtHeaders_t* m_ntHeaders = nullptr;
		NT::ImageDataDirectory_t* m_dataDirectory = nullptr;
		NT::ImageExportDirectory_t* m_exportDirectory = nullptr;
		std::unordered_map<std::string, Address_t> m_exports{};
		std::vector<NT::ImageSectionHeader_t> m_sections{};
		std::span<const std::byte> m_moduleSpan{};
	};

	std::vector<std::byte> ParsePattern(const std::string& pattern);
	Binary_t GetModule(const std::wstring& name);

	// here starts the custom shit :D
	NT::PEB* m_peb;
	HMODULE m_module;
	Address_t m_base;
	Binary_t m_bin;
	Binary_t m_d3d11;
	Binary_t m_dxgi;
	Binary_t m_ntdll;
	Binary_t m_kernel32;

	namespace Addresses {
		bool Setup();

		Address_t m_clientEntityList0;
		Address_t m_clientEntityList1;
		Address_t m_clientState;
		Address_t m_cl_entity_list;
		Address_t m_chlClient;
		Address_t m_engine;
		Address_t m_engineClient;
		Address_t m_input;
		Address_t m_inputSystem;
		Address_t m_gameMovement;
		Address_t m_globalVars;
		Address_t m_globalVars2;
		Address_t m_viewRender;

		Address_t m_localPlayerPtr;
		Address_t m_viewMatrixPtr;
		Address_t m_levelName;

		Address_t m_modelPtr;
	}

	bool Setup(HMODULE _module);
}