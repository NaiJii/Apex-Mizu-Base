#pragma once

namespace NT {
#define IMAGE_SIZEOF_SHORT_NAME 8

	struct UnicodeString_t {
		unsigned short Length;
		unsigned short MaximumLength;
		wchar_t* Buffer;
	};

	struct ImageDosHeader_t {
		unsigned short e_magic;
		unsigned short e_cblp;
		unsigned short e_cp;
		unsigned short e_crlc;
		unsigned short e_cparhdr;
		unsigned short e_minalloc;
		unsigned short e_maxalloc;
		unsigned short e_ss;
		unsigned short e_sp;
		unsigned short e_csum;
		unsigned short e_ip;
		unsigned short e_cs;
		unsigned short e_lfarlc;
		unsigned short e_ovno;
		unsigned short e_res[4];
		unsigned short e_oemid;
		unsigned short e_oeminfo;
		unsigned short e_res2[10];
		long e_lfanew;
	};

	struct ImageFileHeader_t {
		unsigned short Machine;
		unsigned short NumberOfSections;
		unsigned long TimeDateStamp;
		unsigned long PointerToSymbolTable;
		unsigned long NumberOfSymbols;
		unsigned short SizeOfOptionalHeader;
		unsigned short Characteristics;
	};

	struct ImageExportDirectory_t {
		unsigned long Characteristics;
		unsigned long TimeDateStamp;
		unsigned short MajorVersion;
		unsigned short MinorVersion;
		unsigned long Name;
		unsigned long Base;
		unsigned long NumberOfFunctions;
		unsigned long NumberOfNames;
		unsigned long AddressOfFunctions;
		unsigned long AddressOfNames;
		unsigned long AddressOfNameOrdinals;
	};

	struct ImageDataDirectory_t {
		unsigned long VirtualAddress;
		unsigned long Size;
	};

	struct ImageOptionalHeader_t {
		unsigned short Magic;
		unsigned char MajorLinkerVersion;
		unsigned char MinorLinkerVersion;
		unsigned long SizeOfCode;
		unsigned long SizeOfInitializedData;
		unsigned long SizeOfUninitializedData;
		unsigned long AddressOfEntryPoint;
		unsigned long BaseOfCode;
		unsigned long long ImageBase;
		unsigned long SectionAlignment;
		unsigned long FileAlignment;
		unsigned short MajorOperatingSystemVersion;
		unsigned short MinorOperatingSystemVersion;
		unsigned short MajorImageVersion;
		unsigned short MinorImageVersion;
		unsigned short MajorSubsystemVersion;
		unsigned short MinorSubsystemVersion;
		unsigned long Win32VersionValue;
		unsigned long SizeOfImage;
		unsigned long SizeOfHeaders;
		unsigned long CheckSum;
		unsigned short Subsystem;
		unsigned short DllCharacteristics;
		unsigned long long SizeOfStackReserve;
		unsigned long long SizeOfStackCommit;
		unsigned long long SizeOfHeapReserve;
		unsigned long long SizeOfHeapCommit;
		unsigned long LoaderFlags;
		unsigned long NumberOfRvaAndSizes;
		ImageDataDirectory_t DataDirectory[16];
	};

	struct ImageNtHeaders_t {
		unsigned long Signature;
		ImageFileHeader_t FileHeader;
		ImageOptionalHeader_t OptionalHeader;
	};

	struct ImageSectionHeader_t {
		unsigned char Name[IMAGE_SIZEOF_SHORT_NAME];
		union {
			unsigned long PhysicalAddress;
			unsigned long VirtualSize;
		} Misc;
		unsigned long VirtualAddress;
		unsigned long SizeOfRawData;
		unsigned long PointerToRawData;
		unsigned long PointerToRelocations;
		unsigned long PointerToLinenumbers;
		unsigned short NumberOfRelocations;
		unsigned short NumberOfLinenumbers;
		unsigned long Characteristics;
	};

	struct ListEntry_t {
		ListEntry_t* Flink;
		ListEntry_t* Blink;
	};

	struct PEBLdrData_t {
		unsigned long Length;
		unsigned long Initialized;
		const char* SsHandle;
		ListEntry_t InLoadOrderModuleList;
		ListEntry_t InMemoryOrderModuleList;
		ListEntry_t InInitializationOrderModuleList;
	};

	struct PEB {
		unsigned char Reserved1[2];
		unsigned char BeingDebugged;
		unsigned char Reserved2[1];
		const char* Reserved3[2];
		PEBLdrData_t* Ldr;
	};

	struct LdrDataTableEntry_t {
		ListEntry_t InLoadOrderModuleList;
		ListEntry_t InMemoryOrderLinks;
		ListEntry_t InInitializationOrderModuleList;
		void* DllBase;
		void* EntryPoint;
		union {
			unsigned long SizeOfImage;
			const char* _dummy;
		};
		UnicodeString_t FullDllName;
		UnicodeString_t BaseDllName;
	};
}