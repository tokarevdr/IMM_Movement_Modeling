PROJECT_ROOT_PATH = $${PWD}/

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
} else {
    BUILD_FLAG = release
}

IMPORT_PATH = $${PROJECT_ROOT_PATH}/import

BIN_PATH = $${PROJECT_ROOT_PATH}/bin/$${BUILD_FLAG}/

BUILD_PATH = $${PROJECT_ROOT_PATH}/build/$${BUILD_FLAG}/$${TARGET}/
RCC_DIR = $${BUILD_PATH}/rcc/
UI_DIR = $${BUILD_PATH}/ui/
MOC_DIR = $${BUILD_PATH}/moc/
OBJECTS_DIR = $${BUILD_PATH}/obj/

INCLUDEPATH += $${IMPORT_PATH}

QMAKE_CXXFLAGS += -std=c++14
