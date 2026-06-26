# University Transport Management System

A console-based fleet, route, and pass management system for university transport, built in C++ with a layered architecture and full use of core OOP principles — inheritance, polymorphism, encapsulation, and abstraction — across a multi-class system.

/run/media/ammarbinyasir/InternalDrive/Ammar-Personal/University/Semester2/OOP-LAB/OOP-Theory-Project/documentation/UML Diagram.png
<!-- Already in your documentation/ folder — just needs the relative path to render on GitHub -->

## What this project demonstrates

This goes beyond a single-file inheritance demo: the codebase is split into distinct layers, each with a clear responsibility, designed against a UML diagram before implementation (see `documentation/`).

- **Two real inheritance hierarchies** — `User` as a base class for `Admin` and `Student`, and `Vehicle` as a base class for `Bus` and `Van`, both using virtual functions for behavior that differs by subtype
- **A hand-written generic container** (`ClassArray.h`) — a templated dynamic array built from scratch, similar in spirit to `std::vector`, used instead of fixed-size arrays or STL containers
- **Layered architecture** — orchestration (`Engine/`), data + base classes (`core/`), business logic (`modules/`), file persistence (`storage/`), all kept separate rather than mixed into one file
- **File-based persistence** — system state (users, vehicles, routes, passes) is loaded from `.txt` files at startup and saved back on shutdown, handled by a dedicated `FileHandler` class rather than scattered file I/O
- **Console UI as its own layer** (`ConsoleUI`) — menu/display logic is kept separate from business logic in `modules/`

## Architecture

```
Engine/         TransportManager — boots the system, runs the main menu, owns the overall lifecycle
core/           User, Vehicle (base classes), ConsoleUI, ClassArray (custom templated container)
modules/        Admin, Student (User subclasses) · Bus, Van (Vehicle subclasses)
                Route, TransportPass, Bill, Report (domain logic)
storage/        FileHandler — reads/writes users.txt, vehicles.txt, routes.txt, passes.txt
documentation/  UML diagram, system design report, screenshots
```

`main.cpp` follows a clean three-phase lifecycle: boot (`loadSystemData()` reads all four `.txt` files into memory), run (`runMainMenu()` handles login/registration and routes control to the right module polymorphically), and shutdown (`saveSystemData()` writes state back to disk, then the `TransportManager` destructor cleans up all dynamically allocated objects).

## Core OOP concepts in use

- **Inheritance & polymorphism** — `Admin` and `Student` both extend `User`; `Bus` and `Van` both extend `Vehicle`. Shared behavior lives in the base class, while subtype-specific behavior is overridden via virtual functions — for example, an admin's available menu actions differ from a student's, and fare/capacity logic differs between a bus and a van.
- **Encapsulation** — each class keeps its internal state private, exposing only the methods needed to interact with it (registering a user, booking a pass, generating a bill).
- **Abstraction** — `Report` and `Bill` expose simple, high-level operations (generate a report, calculate a bill) without callers needing to know the underlying data layout.
- **Generic programming** — `ClassArray` is a template class, making it reusable across different object types throughout the system rather than writing a separate array implementation per class.

## Tech stack

- **C++** (built with a `Makefile`)
- Custom file-based persistence (no external database)

## Building and running

```bash
git clone https://github.com/Ammar-Bin-Yasir/OOP-Theory-Project.git
cd OOP-Theory-Project
make
./transport_system
```

On first run, the system reads any existing data from `users.txt`, `vehicles.txt`, `routes.txt`, and `passes.txt` — delete these (or back them up) to start with a clean system.

## Documentation

The `documentation/` folder includes the full project report and supporting design diagrams submitted for the course, including the UML class diagram and screenshots of fleet/route management, pass application and billing, and the system controller flow.

## Known limitations / future improvements

- Data persistence is plain-text file based — vulnerable to manual corruption and offers no transaction safety; a real system would use a proper embedded database (e.g. SQLite) instead
- Console-only interface — a natural next step would be wrapping the existing class logic in a simple GUI (Qt) or even a thin web frontend, since the business logic layer is already separated from the UI layer
- No input validation hardening was a focus for this assignment — production use would need stricter validation on all file-loaded and user-entered data

## Background

Originally built as a course project for **CSC-103: Object-Oriented Programming** at the University of Engineering and Technology (UET) Lahore, designed and implemented individually with a UML diagram produced ahead of coding.
