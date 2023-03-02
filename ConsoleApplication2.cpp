#include <stdio.h>
#include <windows.h>

typedef int (*target_func_t)(int);

// Trampoline function that will be used to execute the original code from the target function
int trampoline(int arg) {
	printf("Trampoline function called with argument: %d\n", arg);
	return 0;
}

// Hook function that will be used to intercept calls to the target function
int hook(int arg) {
	printf("Hook function called with argument: %d\n", arg);

	// Perform desired processing

	// Transfer control back to the trampoline function
	return trampoline(arg);
}

int main() {
	// Determine the address of the target function and the code that needs to be replaced
	target_func_t target_func = (target_func_t)GetProcAddress(GetModuleHandle(NULL), "target_func");
	unsigned char* target_code = (unsigned char*)target_func;

	// Calculate the relative address of the trampoline function and store it in a jump instruction
	unsigned char jump_instruction[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
	int trampoline_offset = (int)trampoline - (int)target_func - 5;
	*(int*)(jump_instruction + 1) = trampoline_offset;

	// Overwrite the first few bytes of the target function with the jump instruction
	DWORD old_protect;
	VirtualProtect(target_code, 5, PAGE_EXECUTE_READWRITE, &old_protect);
	memcpy(target_code, jump_instruction, 5);
	VirtualProtect(target_code, 5, old_protect, &old_protect);
}
