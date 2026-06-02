# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# Target executable names
TARGET = transport_system
DEBUG_TARGET = transport_system_debug

# Source files
SRCS = main.cpp \
       core/User.cpp core/Vehicle.cpp \
       modules/Admin.cpp modules/Student.cpp modules/Bus.cpp modules/Van.cpp \
       modules/Route.cpp modules/TransportPass.cpp modules/Bill.cpp modules/Report.cpp \
       storage/FileHandler.cpp \
       Engine/TransportManager.cpp

# Rules
all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

debug:
	$(CXX) $(CXXFLAGS) -g $(SRCS) -o $(DEBUG_TARGET)

clean:
	rm -f $(TARGET) $(DEBUG_TARGET)
