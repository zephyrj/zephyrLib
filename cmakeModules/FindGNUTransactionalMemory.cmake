# Find the gnu-tm development library.
#
# GNUTransactionalMemory_LIBRARIES - Library for gnu-tm
# GNUTransactionalMemory_FOUND	- True if gnu-tm found

# Look for the library.
FIND_LIBRARY(GNUTransactionalMemory_LIBRARY NAMES gnu-tm)

# Handle the QUIETLY and REQUIRED arguments and set Systemd_FOUND to TRUE if all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GNUTransactionalMemory DEFAULT_MSG GNUTransactionalMemory_LIBRARY)

# Copy the results to the output variables.
IF(GNUTransactionalMemory_FOUND)
    SET(GNUTransactionalMemory_LIBRARIES ${GNUTransactionalMemory_LIBRARY})
ELSE()
    SET(GNUTransactionalMemory_LIBRARIES)
ENDIF()

MARK_AS_ADVANCED(GNUTransactionalMemory_LIBRARIES)