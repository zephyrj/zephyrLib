# Find the GNU Transactional Memory (libitm) library.
#
# GNUTransactionalMemory_LIBRARIES - Library for gnu-tm
# GNUTransactionalMemory_FLAG - Compiler flag for gnu-tm
# GNUTransactionalMemory_FOUND - True if gnu-tm found
# TODO work out how to do this properly

# Look for the library.
FIND_LIBRARY(GNUTransactionalMemory_LIBRARY NAMES itm)

# Handle the QUIETLY and REQUIRED arguments and set Systemd_FOUND to TRUE if all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GNUTransactionalMemory DEFAULT_MSG GNUTransactionalMemory_LIBRARY)

# Copy the results to the output variables.
IF(GNUTransactionalMemory_FOUND)
    SET(GNUTransactionalMemory_LIBRARIES ${GNUTransactionalMemory_LIBRARY})
    SET(GNUTransactionalMemory_FLAG "-fgnu-tm")
ELSE()
    SET(GNUTransactionalMemory_LIBRARIES)
    SET(GNUTransactionalMemory_FLAG)
ENDIF()

MARK_AS_ADVANCED(GNUTransactionalMemory_LIBRARIES)