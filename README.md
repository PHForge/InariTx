# InariTx 🦊

Transform your crypto transactions into clear, verifiable, professional receipts with unparalleled simplicity.

![Language](https://img.shields.io/badge/language-C++-blue.svg) ![License](https://img.shields.io/badge/license-MIT-darkblue.svg) ![SoftVersion](https://img.shields.io/badge/SoftVersion-0.0.1-Red) 

<br>

## Overview 🔍

InariTx is a C++ application designed to generate professional receipts for cryptocurrency transactions. It leverages blockchain data to create PDF receipts with embedded QR codes for transaction verification, supporting internationalization and JSON-based configuration. The project uses the following libraries:

- **[libharu](https://github.com/libharu/libharu)**: Generates PDF files for receipts.
- **[qrcodegen](https://github.com/nayuki/QR-Code-generator)**: Creates QR codes for transaction verification.
- **[nlohmann/json](https://github.com/nlohmann/json)**: Handles JSON parsing for configuration and blockchain data.
- **[libcurl](https://curl.se/libcurl/)**: Performs HTTP requests to fetch blockchain data (e.g., Bitcoin transaction details).

<br>

## Features 📋

InariTx aims to provide a seamless experience for generating professional cryptocurrency transaction receipts. Below are the planned features, leveraging C++ libraries for robust and secure implementation:

- **Generates PDF receipts from blockchain transactions (Bitcoin focus)**  
  - Fetches transaction details (sender/receiver addresses, amount in BTC, date, timestamp) using a public blockchain API (e.g., Blockcypher) or a Bitcoin node.  
  - Produces professional, human-readable PDF receipts with a clean layout (e.g., InariTx header, clear fonts).  
  - Supports custom metadata (e.g., sender/receiver names) to enhance receipt details.  
  - *Implementation*: Uses **libharu** for PDF generation, with data fetched via **libcurl** and parsed using **nlohmann/json**.

- **Embeds QR codes in PDFs for transaction verification**  
  - Includes a scannable QR code linking to a blockchain explorer (e.g., `https://blockchain.com/btc/tx/[TXID]`) for instant transaction verification.  
  - Integrates the QR code alongside transaction details in the PDF.  
  - *Implementation*: Uses **qrcodegen** to generate QR codes, embedded into PDFs via **libharu**.

- **User account management for history and preferences**  
  - Allows users to create accounts to track transaction history, download past PDF receipts, and manage preferences (e.g., email, password, language).  
  - Features include:  
    - Transaction history with TXID and downloadable PDFs.  
    - Email and password updates with secure handling.  
    - Language selection for internationalization (e.g., via flags or settings).  
  - *Implementation*: Uses a lightweight database (e.g., SQLite with sqlcipher for encryption) and a REST API built with a C++ framework (e.g., Crow).

- **Custom metadata for professional receipts**  
  - Enables users to add metadata (e.g., company name, service description, invoice number) to receipts for accounting or professional use.  
  - Provides a simple web or API form to input metadata, integrated into the PDF (e.g., as a header).  
  - *Implementation*: Combines HTML form input with a C++ REST API to inject metadata into PDFs using **libharu**.

- **Freemium subscription model**  
  - Offers a tiered subscription plan with free and premium features (e.g., unlimited receipt generation, advanced statistics for premium users).  
  - *Implementation*: Integrates subscription logic via a REST API, with user data stored in SQLite.

- **Guest mode for one-off PDF generation**  
  - Allows non-registered users to generate PDF receipts by entering a TXID, with direct download and no storage.  
  - Provides a simple web interface or public API endpoint (e.g., `/inaritx/generate/[TXID]`).  
  - *Implementation*: Uses a C++ REST API (e.g., Crow) with **libcurl** for blockchain data and **libharu** for PDF output.

- **Automatic TXID validation**  
  - Validates transaction IDs (TXIDs) in real-time before generating receipts to prevent errors.  
  - Displays clear error messages for invalid TXIDs.  
  - *Implementation*: Uses **libcurl** to query a blockchain API (e.g., Blockcypher) and **nlohmann/json** to parse responses.

- **Basic statistics for subscribers**  
  - Provides simple analytics for premium users, such as the number of receipts generated or total transaction amounts.  
  - Includes basic visualizations (e.g., receipts per month).  
  - *Implementation*: Stores data in SQLite, with a frontend rendering graphs via a web interface.

- **API module for integration with professional software**  
  - Offers a REST API for third-party software to generate receipts programmatically.  
  - Supports secure integration with external accounting or blockchain tools.  
  - *Implementation*: Built with a C++ REST framework (e.g., Crow) and **libcurl** for blockchain data retrieval.

- **Cross-platform compatibility**  
  - Ensures the application builds and runs on Windows, Linux, and macOS using CMake.  
  - Supports UTF-8 encoding for internationalization and consistent display across platforms.  
  - *Implementation*: Leverages CMake for build configuration and **nlohmann/json** for configuration parsing.

<br>

## System Requirements ⚙️

The following components are required to build, run, or contribute to this project:

| Component          | Requirement                              | Notes                                      |
|--------------------|------------------------------------------|--------------------------------------------|
| **Language**       | C++20                                    | Core language used for the project         |
| **Compiler**       | GCC (via MSYS2 UCRT64)                   | Ensure G++ is installed; other compilers like Clang or MSVC may work with CMake |
| **Libraries**      | `cpp-httplib`, `nlohmann/json`, OpenSSL, WinSock (`ws2_32`), `crypt32` | Header-only libraries (`cpp-httplib`, `nlohmann/json`) included in `include/`; OpenSSL installed via MSYS2 |
| **Build System**   | CMake 3.15 or higher                     | Used for cross-platform build configuration |
| **IDE/Editor**     | VS Code (recommended) or any C++-compatible IDE/terminal | Configured with `tasks.json` and `launch.json` for compilation and debugging |
| **Debugger**       | GDB (via MSYS2 UCRT64)                   | For debugging in VS Code                   |
| **Version Control**| Git                                      | Required to clone the repository           |
| **OS**             | Windows (tested with MSYS2 UCRT64); Linux/macOS (with adjustments) | CMake ensures cross-platform compatibility; UTF-8 support required for ANSI colors and progress bar |


> [!TIP]
> For an optimal setup on Windows, install [MSYS2 UCRT64](https://www.msys2.org/) and use the following command to install dependencies:
> ```bash
> pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-openssl mingw-w64-ucrt-x86_64-gdb
> ```
> On Linux/macOS, use package managers like `apt` or `brew` to install `g++`, `cmake`, `openssl`, and `git`.

<br>

## Setup 🛠️

1. **Install dependencies** (on MSYS2/MINGW64):
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-git
   pacman -S mingw-w64-x86_64-libharu mingw-w64-x86_64-qr-code-generator mingw-w64-x86_64-nlohmann-json
   pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-openssl mingw-w64-x86_64-zlib mingw-w64-x86_64-libidn2 mingw-w64-x86_64-libssh2 mingw-w64-x86_64-libpsl mingw-w64-x86_64-brotli mingw-w64-x86_64-zstd mingw-w64-x86_64-nghttp2
   ```
2. **Download cacert.pem**:
    ```bash
    cd /c/Users/Pinohell2/Desktop/Learning_Cpp/InariTx
    curl -o cacert.pem https://curl.se/ca/cacert.pem
    ```
    Place cacert.pem in the project root directory (InariTx/). This file is required for secure HTTPS requests and is ignored by .gitignore.
3. **Clone the repository**:
    ```bash
    git clone https://github.com/PHForge/InariTx.git
    cd InariTx
    ```
4. **Build the project**:
    ```bash
    mkdir build && cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    ```
5. **Run the application**:
    ```bash
    ./InariTx
    ```
<br>

## Project Structure 🗂️

    InariTx/
    ├── src/                      	# Source code for the application
    │   ├── main.cpp              	# Entry point for the command-line interface (CLI) application
    │   ├── blockchain/           	# Logic for interacting with blockchain data
    │   │   ├── client.h          	# Abstract interface for blockchain clients (defines common methods)
    │   │   ├── client.cpp        	# Implementation of the blockchain client interface
    │   │   ├── bitcoin_client.h  	# Bitcoin-specific client interface for fetching transaction data
    │   │   └── bitcoin_client.cpp 	# Implementation of Bitcoin client using libcurl for API requests
    │   ├── pdf/                  	# PDF generation logic for creating receipts
    │   │   ├── pdf_generator.h   	# Header for PDF generation functions
    │   │   └── pdf_generator.cpp 	# Implementation using libharu to generate PDF receipts
    │   ├── qr/                   	# QR code generation logic for transaction verification
    │   │   ├── qr_generator.h    	# Header for QR code generation functions
    │   │   └── qr_generator.cpp  	# Implementation using qrcodegen to create QR codes
    │   ├── i18n/                 	# Internationalization support for multiple languages
    │   │   ├── translations.h    	# Header for managing translations (e.g., English, French)
    │   │   └── translations.cpp  	# Implementation of translation logic
    │   ├── utils/                	# Utility functions for common tasks
    │   │   ├── error.h           	# Header for error handling and custom exceptions
    │   │   ├── error.cpp         	# Implementation of error handling
    │   │   ├── config.h          	# Header for configuration management (e.g., API keys, settings)
    │   │   └── config.cpp        	# Implementation of configuration parsing using nlohmann/json
    ├── include/                  	# Third-party library headers
    │   ├── libharu/              	# Headers for libharu (PDF generation library)
    │   ├── qrcodegen/            	# Headers for qrcodegen (QR code generation library)
    │   ├── nlohmann/             	# Header for nlohmann/json (JSON parsing library)
    │   └── curl/                 	# Headers for libcurl (HTTP request library)
    ├── lib/                      	# Static libraries for linking
    │   ├── libcurl.a             	# Static library for libcurl (HTTP requests)
    │   ├── libhpdf.a             	# Static library for libharu (PDF generation)
    │   └── libqrcodegen.a        	# Static library for qrcodegen (QR code generation)
    ├── docs/                     	# Documentation files
    │   ├── CHANGELOG.md          	# Version history and release notes
    │   └── ARCHITECTURE.md       	# Overview of the project's architecture and design
    ├── docker/                   	# Docker configuration for deployment
    │   └── Dockerfile            	# Dockerfile for building and running InariTx on platforms like RunOnFlux
    ├── cacert.pem                	# Certificate Authority bundle for libcurl HTTPS requests (ignored by .gitignore)
    ├── CMakeLists.txt            	# CMake configuration for building the project
    ├── .gitignore                	# Git ignore file (excludes build/, cacert.pem, *.pdf, etc.)
    ├── LICENSE                   	# MIT License file
    └── README.md                 	# Project documentation and setup instructions

<br>

## Contributing 🤝

Contributions are welcome! To contribute:

- Fork the repository.
- Create a new branch (`git checkout -b feature/your-feature`).
- Make your changes and commit them (`git commit -m "Add your feature"`).
- Push to the branch (`git push origin feature/your-feature`).
- Open a pull request on GitHub.

Please ensure your code follows the project's coding style and includes appropriate documentation.

<br>

## License 🧾

This project is licensed under the **MIT License** - see the LICENSE file for details.

<br>

## Crédits ☕

> Developed by PHForge. 
> Feel free to reach out via [GitHub](https://github.com/PHForge) for feedback or collaboration ideas!

> Special thanks ❤️ to my wife and son for their patience and love.