Inline hooking is a technique used to intercept calls to target functions. It is commonly used by antiviruses, sandboxes, and malware to perform a variety of tasks, such as checking parameters, shimming, logging, spoofing returned data, and filtering calls.

The process of inline hooking involves directly modifying the code within the target function, usually by overwriting the first few bytes with a jump instruction to redirect execution to a different function. This allows processing to be performed before or after the target function executes. Rootkits often use hooks to modify data returned from system calls to hide their presence, while security software uses them to prevent or monitor potentially malicious operations.

The hooks are placed by directly modifying code within the target function (inline modification), usually by overwriting the first few bytes with a jump; this allows execution to be redirected before the function does any processing. Most hooking engines use a 32-bit relative jump (opcode 0xE9), which takes up five bytes of space.

Here is a general outline of the process of implementing an inline hook:

Determine the address of the target function and the code that needs to be replaced.

Create a trampoline function that will be used to execute the original code from the target function after the hook has been applied.

Calculate the relative address of the trampoline function and store it in a jump instruction.

Overwrite the first few bytes of the target function with the jump instruction.

Modify the hook function to transfer control back to the trampoline function after performing the desired processing.
