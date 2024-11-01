vcpkg_download_distfile(LINUX_PATCH
    URLS https://github.com/microsoft/cppgraphqlgen/commit/aa02e66edcf248c61a198eec546c401c3ada3667.patch?full_index=1
    FILENAME fix-linux.patch
    SHA512 d3664dbcc1a8df0eb538e82a932d3df16697b2f457039faa8b6cf6b95d3381f92de23433936f7196502db6afa9c8f58197194a65a87437092c1eb1cad684d652
)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO microsoft/cppgraphqlgen
    REF "v${VERSION}"
    SHA512 1de45784485c285890200d31ce228a55ba19ed0d1bf0a3c18ea3c73d1938269f25833da1c28e8e155d875bdcf2fdf9916872f30ef9946de6bf58c1dfde451f4b
    HEAD_REF main
    PATCHES
        ${LINUX_PATCH}
)

vcpkg_check_features(
    OUT_FEATURE_OPTIONS FEATURE_OPTIONS
    FEATURES
        clientgen   GRAPHQL_BUILD_CLIENTGEN
        rapidjson   GRAPHQL_USE_RAPIDJSON
        schemagen   GRAPHQL_BUILD_SCHEMAGEN
)

vcpkg_cmake_configure(
    SOURCE_PATH ${SOURCE_PATH}
    OPTIONS 
        -DGRAPHQL_BUILD_TESTS=OFF 
        -DGRAPHQL_UPDATE_VERSION=OFF 
        -DGRAPHQL_UPDATE_SAMPLES=OFF 
        -DGRAPHQL_INSTALL_CONFIGURATIONS=Release
        ${FEATURE_OPTIONS}
    OPTIONS_RELEASE 
        -DGRAPHQL_INSTALL_CMAKE_DIR=${CURRENT_PACKAGES_DIR}/share 
        -DGRAPHQL_INSTALL_TOOLS_DIR=${CURRENT_PACKAGES_DIR}/tools
    OPTIONS_DEBUG 
        -DGRAPHQL_INSTALL_CMAKE_DIR=${CURRENT_PACKAGES_DIR}/debug/share 
        -DGRAPHQL_INSTALL_TOOLS_DIR=${CURRENT_PACKAGES_DIR}/debug/tools
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup()

vcpkg_list(SET TOOL_NAMES)
if (GRAPHQL_BUILD_CLIENTGEN)
	vcpkg_list(APPEND TOOL_NAMES clientgen)
endif()
if (GRAPHQL_BUILD_SCHEMAGEN)
	vcpkg_list(APPEND TOOL_NAMES schemagen)
endif()

if(TOOL_NAMES)
	vcpkg_copy_tools(
	    TOOL_NAMES ${TOOL_NAMES}
	    SEARCH_DIR ${CURRENT_PACKAGES_DIR}/tools/cppgraphqlgen)
endif()

vcpkg_copy_pdbs()

file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
