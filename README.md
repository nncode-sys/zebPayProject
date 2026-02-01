# ProjectZebPay – Build & Run Instructions (C++)

This document provides complete instructions to build and run the
ProjectZebPay C++ Order Book Aggregator project using Eclipse IDE
on Windows (Debug configuration).

------------------------------------------------------------
1. PROJECT OVERVIEW
------------------------------------------------------------

ProjectZebPay is a C++ order book aggregator that:
- Fetches order book data from multiple crypto exchanges
- Aggregates bids and asks across exchanges
- Calculates total buy cost / sell revenue
- Computes volume-weighted average buy and sell prices
- Provides execution breakdown (quantity filled per exchange)

The project uses:
- C++17
- libcurl for HTTP requests
- nlohmann/json for JSON parsing
- Eclipse IDE (C/C++)

------------------------------------------------------------
2. EXPECTED PROJECT STRUCTURE
------------------------------------------------------------

Ensure the project structure is exactly as follows:

ProjectZebPay/
│
├── src/
│   ├── core/
│   │   ├── defines.hpp
│   │   ├── defines.cpp
│   │   ├── Exchange.hpp
│   │   ├── RateLimiter.hpp
│   │   └── json.hpp
│   │
│   ├── exchanges/
│   │   ├── Coinbase.cpp
│   │   └── Gemini.cpp
│   │
│   ├── Aggregator.hpp
│   └── main.cpp
│
├── Debug/
│   ├── libcurl-x64.dll
│
└── README.md

IMPORTANT:
- No .cpp file is included inside another .cpp file
- Headers (.hpp) contain declarations only
- Implementations are in .cpp files

------------------------------------------------------------
3. SYSTEM REQUIREMENTS
------------------------------------------------------------

Operating System:
- Windows 10 / Windows 11 (64-bit)

Tools Required:
- Eclipse IDE for C/C++ Developers
- MinGW-w64 (GCC 64-bit)
- libcurl (Windows build)
- Internet connection (for API calls)

------------------------------------------------------------
4. INSTALL REQUIRED TOOLS
------------------------------------------------------------

4.1 Install Eclipse IDE

1. Download Eclipse from:
   https://www.eclipse.org/downloads/
2. Select "Eclipse IDE for C/C++ Developers"
3. Install and launch Eclipse

------------------------------------------------------------

4.2 Install MinGW-w64 (GCC)

1. Install MinGW-w64 (64-bit)
2. Choose:
   - Architecture: x86_64
   - Threads: posix
3. Add MinGW bin directory to System PATH

Verify installation:
   g++ --version

------------------------------------------------------------

4.3 Install libcurl (Windows)

1. Download libcurl for Windows from:
   https://curl.se/windows/

2. Extract the archive and locate:
   - libcurl-x64.dll
   - include/curl/*.h
   - libcurl.a or libcurl.dll.a

------------------------------------------------------------
5. IMPORT PROJECT INTO ECLIPSE
------------------------------------------------------------

1. Open Eclipse
2. Go to:
   File → Import → Existing Projects into Workspace
3. Select the ProjectZebPay root directory
4. Click Finish

------------------------------------------------------------
6. CONFIGURE ECLIPSE BUILD SETTINGS
------------------------------------------------------------

6.1 Include Paths

Go to:
Project → Properties → C/C++ General → Paths and Symbols

Add include paths:
- src/
- src/core/

Add libcurl include path:
- <path-to-libcurl>/include

------------------------------------------------------------

6.2 Linker Settings (IMPORTANT)

Go to:
Project → Properties → C/C++ Build → Settings
→ MinGW C++ Linker → Libraries

Add:
- Library name: curl
- Library path: <path-to-libcurl>/lib

------------------------------------------------------------

6.3 Compiler Standard

Go to:
Project → Properties → C/C++ Build → Settings
→ GCC C++ Compiler → Dialect

Set:
- Language standard: ISO C++17

------------------------------------------------------------
7. POST-BUILD STEP (IMPORTANT)
------------------------------------------------------------

To ensure the executable runs correctly, the libcurl runtime DLL
must be present in the Debug output directory.

Add the following **Post-build command** in Eclipse:

1. Go to:
   Project → Properties → C/C++ Build → Settings
   → Build Steps → Post-build steps

2. Add this command:

   copy /Y "C:\path\to\libcurl-x64.dll" "${BuildArtifactFileBaseName}/../Debug/"

OR (recommended):

   copy /Y "C:\path\to\libcurl-x64.dll" "${BuildArtifactFileDir}"

This command copies the libcurl DLL from the system location
into the Debug folder automatically after every build.

------------------------------------------------------------
8. BUILD THE PROJECT
------------------------------------------------------------

1. Ensure build configuration is set to Debug
2. Right-click the project → Build Project
3. Confirm there are no compilation or linker errors

Output binary:
- Debug/ProjectZebPay.exe

------------------------------------------------------------
9. RUN THE PROJECT
------------------------------------------------------------

Option 1: Run from Eclipse
- Right-click project → Run As → Local C/C++ Application

Option 2: Run from Command Line
   cd Debug
   ProjectZebPay.exe

IMPORTANT:
- libcurl-x64.dll must be present in the Debug folder

------------------------------------------------------------
10. EXPECTED OUTPUT
------------------------------------------------------------

Example output:

Average Buy Price: 100.83
Coinbase : 6 BTC
Gemini   : 4 BTC

------------------------------------------------------------
11. AVERAGE COST LOGIC
------------------------------------------------------------

Average price is calculated using VWAP:

Average Price =
Σ(price × filled_quantity) / Σ(filled_quantity)

------------------------------------------------------------
12. COMMON BUILD ERRORS & FIXES
------------------------------------------------------------

Error: curl/curl.h not found
Fix: Add libcurl include path in Eclipse

Error: undefined reference to curl_easy_*
Fix: Link libcurl in linker settings

Error: Program crashes at runtime
Fix:
- Ensure libcurl-x64.dll is copied via post-build step
- Ensure correct 64-bit architecture

------------------------------------------------------------
13. CLEAN REBUILD (IF REQUIRED)
------------------------------------------------------------

Project → Clean → Clean all projects
Then rebuild.

------------------------------------------------------------
14. DESIGN NOTES (FOR EVALUATORS)
------------------------------------------------------------

- One Definition Rule (ODR) is respected
- No .cpp file inclusion
- Clean exchange abstraction
- Financially correct VWAP calculations
- Modular and extensible design

------------------------------------------------------------
AUTHOR
------------------------------------------------------------

Narendra Jatav
C++ | Systems | Trading Infrastructure

------------------------------------------------------------
END OF BUILD INSTRUCTIONS
------------------------------------------------------------
