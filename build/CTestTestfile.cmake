# CMake generated Testfile for 
# Source directory: C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code
# Build directory: C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test1 "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/build/Debug/orbitalsim_test.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;35;add_test;C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test1 "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/build/Release/orbitalsim_test.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;35;add_test;C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test1 "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/build/MinSizeRel/orbitalsim_test.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;35;add_test;C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test1 "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/build/RelWithDebInfo/orbitalsim_test.exe")
  set_tests_properties(test1 PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;35;add_test;C:/Users/santi/OneDrive/Documentos/1a.-Warm-Up---Starter-Code/1a.-Warm-Up---Starter-Code/CMakeLists.txt;0;")
else()
  add_test(test1 NOT_AVAILABLE)
endif()
