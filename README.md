# PlaguewareCSGO 3.0 – A Research-Driven Exploration of Game Memory Exploitation and Kernel-Level Evasion Techniques

> **Version**: 3.0  
> **Study Period**: Originally researched and developed in 2021
> **Purpose**: Academic research into game security, memory manipulation, and anti-cheat evasion  
> **Disclaimer**: This project is a technical exploration and is not intended for practical use in any production or competitive environment.

## Background & Scope

PlaguewareCSGO 3.0 examines the internal structure of the Source Engine (used by CS:GO) and explores how vulnerabilities in third-party software can be used to gain unauthorized access to protected game memory. It uses a vulnerable, signed driver (`RTCore64.sys`) to demonstrate kernel-level exploitation techniques as part of a documented case study.

The cheat logic itself is implemented entirely in C++, with dynamic scanning, modular hooks, and runtime memory protection mechanisms that emulate modern internal game cheats.



## Exploitation Techniques Explored

### 1. Vtable Hooking
- Cloning and overwriting virtual function tables of Source engine interfaces (e.g., `IClientMode`) to redirect game behavior.
- Implemented using shadow vtables and memory protection manipulation (`VirtualProtect`).

### 2. Signature Scanning
- Locating engine functions and objects dynamically through pattern matching.
- Avoids reliance on hardcoded offsets and improves resilience across updates.

### 3. Kernel-Mode Exploitation (BYOVD)
- Uses RTCore64.sys, a vulnerable signed driver, to gain kernel-level read/write access to memory.
- Demonstrates how driver IOCTLs can be abused to:
  - Bypass anti-cheat protections
  - Inject code from kernel space
  - Patch or cloak memory regions

### 4. Anti-Detection Techniques
- Encrypted string usage to evade static signature scans.
- Optional unhooking and rehooking logic to dynamically detach from the game runtime.
- Use of ring0 access to bypass user-mode protections.



## Execution Timeline

This timeline outlines the execution flow of the research code from initial setup to cleanup, with a focus on how kernel-level access interacts with the game memory.

| Phase         | Activity                                                                                     |
|---------------|----------------------------------------------------------------------------------------------|
| Initialization | The research driver (`RTCore64.sys`) is loaded into the system using Windows service APIs. This driver grants kernel-level privileges to the user-mode application through exposed IOCTL interfaces. |
| Kernel Communication Setup | A user-mode module establishes communication with the driver using `DeviceIoControl`, preparing to issue memory access commands. |
| Signature Scanning | From kernel or protected user-space, signature scanning is performed to identify the locations of key CS:GO engine modules (e.g., `client.dll`, `engine.dll`) and internal data structures. |
| Interface Resolution | The cheat resolves key Source Engine interfaces (such as `IClientMode`, `IVEngineClient`) by accessing `CreateInterface` exports and dynamically locating vtables. |
| Hook Preparation | Shadow copies of target vtables are created in user memory. Hooks are prepared for functions like `CreateMove`, `DrawModelExecute`, `OverrideView`, and `PaintTraverse`. |
| Kernel-Backed Injection | The driver is used to write the modified vtables and function hooks into the CS:GO process. If needed, additional shellcode or cheat logic is mapped directly into game memory. |
| Runtime Execution | The cheat becomes fully operational. Hooked functions execute per frame, running features such as aimbot logic, glow/ESP rendering, and skin manipulation with anti-detection precautions. |
| Evasion Handling | Optional evasion strategies activate based on triggers or timers. These may include restoring original vtables, toggling visibility of threads or memory, or cloaking injected regions. |
| Cleanup | Upon termination or manual trigger, the cheat restores all original memory regions and vtable pointers, terminates kernel communication, and unloads the driver. No persistent changes are left behind. |



## Related Vulnerabilities Studied

| CVE ID        | Description                                        |
|---------------|----------------------------------------------------|
| CVE-2019-16098 | Arbitrary memory access in RTCore64.sys           |
| CVE-2024-1443 | DoS via IOCTL (0x80002000) in RTCore64.sys         |
| CVE-2024-1460 | Kernel memory leak via IOCTL (0x80002040)          |
| CVE-2024-3745 | ACL bypass to exploit other RTCore64.sys flaws     |

> Patch Note: MSI addressed these in Afterburner 4.6.6 Beta 4 (May 2024)



## Ethical Disclosure

This repository has been published with several critical modifications to ensure that it cannot be used for malicious or unauthorized purposes:

- Executable injection routines have been removed, including any `DllMain` or loader logic that would allow the binary to be injected into a running process.
- Driver loading and IOCTL abuse code for RTCore64.sys has been removed to prevent the unsafe use of vulnerable drivers.
- Automation scripts or injector templates that would assist in deploying the cheat have also been excluded.

These components were stripped from the repository to ensure that the project remains strictly academic and demonstrative, and cannot function as a working cheat without significant reverse engineering and development effort.

The project is intended as a reference point for:
- Understanding how internal game memory structures operate.
- Demonstrating how vulnerable kernel drivers can be exploited — with parallels to real-world attacks.
- Raising awareness of gaps in game and driver security design.

> No precompiled binaries are provided.  
> No complete end-to-end working cheat can be compiled from this repository.




## Final Disclaimer

This repository is published for educational and informational purposes only. Any use of this project to violate software terms of service, engage in online cheating, or perform unauthorized access to computer systems is strictly forbidden and not condoned by the author.

By accessing this repository, you agree to use the material solely for ethical, research-based, and lawful purposes.


## Acknowledgments

- Written by [Rydersel](https://github.com/Rydersel) and [Niko Obama](https://github.com/nikoobama)  
- Project Merge from 2.0 – Shonax  
- Launcher Networking Infrastructure by [Harold](https://github.com/ZECHEESELORD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
