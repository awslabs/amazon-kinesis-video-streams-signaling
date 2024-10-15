# Include filepaths for source and include.
include( ${MODULE_ROOT_DIR}/signalingFilePaths.cmake )
include( ${MODULE_ROOT_DIR}/source/dependency/coreJSON/jsonFilePaths.cmake )

# ====================  Define your project name (edit) ========================
set( project_name "signaling_api" )

message( STATUS "${project_name}" )

# =====================  Create your mock here  (edit)  ========================

# List the files to mock here.
list(APPEND mock_list
            "${MODULE_ROOT_DIR}/source/include/signaling_data_types.h"
        )
# List the directories your mocks need.
list(APPEND mock_include_list
            ${SIGNALING_INCLUDE_PUBLIC_DIRS}
            ${JSON_INCLUDE_PUBLIC_DIRS}
            ${MODULE_ROOT_DIR}/test/unit-test
        )

# List the definitions of your mocks to control what to be included.
list(APPEND mock_define_list
            ""
       )

# ================= Create the library under test here (edit) ==================

# List the files you would like to test here.
list(APPEND real_source_files
            ${MODULE_ROOT_DIR}/source/signaling_api.c
            ${JSON_SOURCES}
        )
# List the directories the module under test includes.
list(APPEND real_include_directories
            ${SIGNALING_INCLUDE_PUBLIC_DIRS}
            ${JSON_INCLUDE_PUBLIC_DIRS}
            ${MODULE_ROOT_DIR}/test/unit-test
            ${CMOCK_DIR}/vendor/unity/src
            ${JSON_SOURCES}
        )

# =====================  Create UnitTest Code here (edit)  =====================

# list the directories your test needs to include.
list(APPEND test_include_directories
            ${CMOCK_DIR}/vendor/unity/src
            ${SIGNALING_INCLUDE_PUBLIC_DIRS}
            ${JSON_INCLUDE_PUBLIC_DIRS}
            ${MODULE_ROOT_DIR}/test/unit-test
        )

# =============================  (end edit)  ===================================

set(mock_name "${project_name}_mock")
set(real_name "${project_name}_real")

create_mock_list(${mock_name}
                "${mock_list}"
                "${MODULE_ROOT_DIR}/test/unit-test/cmock/project.yml"
                "${mock_include_list}"
                "${mock_define_list}"
        )

create_real_library(${real_name}
                    "${real_source_files}"
                    "${real_include_directories}"
                    "${mock_name}"
        )

list(APPEND utest_link_list
            lib${real_name}.a
        )

list(APPEND utest_dep_list
            ${real_name}
        )

set(utest_name "${project_name}_utest")
set(utest_source "${project_name}/${project_name}_utest.c")

create_test(${utest_name}
            ${utest_source}
            "${utest_link_list}"
            "${utest_dep_list}"
            "${test_include_directories}"
        )
