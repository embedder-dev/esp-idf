# Embedder Agent Tools Summary

## File Operations

| Tool | Description |
|------|-------------|
| **readFile** | Read file contents with optional line offset and limit for pagination. Supports text and image files. |
| **writeFile** | Create a new file or completely overwrite an existing file. |
| **editFile** | Perform targeted string replacements in files. Supports single or bulk (`replaceAll`) replacements. |
| **listDirectory** | List directory contents (files/subdirectories) with optional recursion depth (max 5). |
| **glob** | Find files matching glob patterns (e.g., `src/**/*.ts`). Returns absolute paths sorted by modification time. |
| **grep** | Search file contents using regex patterns. Supports case sensitivity and file pattern filtering. |

## Shell & Execution

| Tool | Description |
|------|-------------|
| **shell** | Execute bash commands in a persistent shell session. Supports working directory, timeout, and serial disconnect options. |

## Code Intelligence (LSP)

| Tool | Description |
|------|-------------|
| **lsp** | Language Server Protocol operations: go-to-definition, find-references, hover, document/workspace symbols, go-to-implementation, call hierarchy (incoming/outgoing calls). |

## Serial & Hardware Communication

| Tool | Description |
|------|-------------|
| **serialMonitor** | Open a serial monitor to capture device output. Supports stop-string detection, reset methods (DTR, RTS, DTR+RTS, command), and startup commands. |
| **serialReadHistory** | Read buffered serial output without waiting. Lists all monitors or returns buffered output from a specific port. Supports `only_new` polling. |
| **serialSendCommand** | Send a command to a serial device (UART or RTT) and return the response. Auto-connects if needed. |

## Search & Research

| Tool | Description |
|------|-------------|
| **documentSearch** | Semantic search across loaded hardware documentation using vector embeddings. |
| **codeSearch** | Search for programming context — library docs, API references, code examples. Adjustable token count (1K–50K). |
| **webSearch** | Real-time web search with live crawling modes (`fallback`/`preferred`) and search depth (`auto`/`fast`/`deep`). |
| **webFetch** | Fetch and parse content from a URL. Returns markdown, plain text, or raw HTML. |

## Hardware & Schematic

| Tool | Description |
|------|-------------|
| **schematicInfo** | Retrieve parsed schematic data: pin mappings, net connections, I2C addresses, power domains, component details, interfaces, and busses. |

## Delegation & Subagents

| Tool | Description |
|------|-------------|
| **delegateSubagent** | Launch specialized autonomous subagents for complex tasks. Types: `codebase-explorer` (read-only codebase navigation), `document-explorer` (datasheet/docs research), `web-searcher` (internet research), `planning-agent` (implementation planning). |

## Task Management

| Tool | Description |
|------|-------------|
| **todoRead** | Read the current todo list to check progress and remaining tasks. |
| **todoWrite** | Create and manage a structured task list with statuses: `pending`, `in_progress`, `completed`, `cancelled`. |

## Memory (Persistent Across Sessions)

| Tool | Description |
|------|-------------|
| **saveMemory** | Save a project memory entry (pattern, preference, decision, or issue) with tags, keywords, and content. |
| **memorySearch** | Search memories by keyword across previews, keywords, paths, and content. |
| **memoryListArea** | List memory entries filtered by a broad area tag. |
| **memoryExpand** | Expand memory entry IDs into full detailed content. |
| **forgetMemory** | Remove an outdated or incorrect memory entry. |

## User Interaction

| Tool | Description |
|------|-------------|
| **askQuestion** | Ask the user up to 4 multiple-choice questions with single or multi-select options. |

## Mode Switching

| Tool | Description |
|------|-------------|
| **switchMode** | Switch to `plan` mode (research & design before coding) or `debug` mode (GDB, logic analyzer, serial, PPK2 debugging). |
| **submitPlan** | Submit a completed plan for user approval before implementation. |

## Project Setup

| Tool | Description |
|------|-------------|
| **initProject** | Analyze the codebase and create/improve an `EMBEDDER.md` file with project context, build commands, debug config, and code style. |

## Skills

| Tool | Description |
|------|-------------|
| **loadSkill** | Load a specialized workflow defined in a SKILL.md file. Skills cover areas like debugging (GDB, Saleae, PPK2, RTT, serial), platform support (STM32, nRF/Zephyr, Infineon AURIX), plotting, and more. |
