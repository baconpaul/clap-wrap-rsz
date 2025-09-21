cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11 CACHE STRING "Build for 10.11")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

project(clap-wrap-rsz VERSION 0.9.0 LANGUAGES CXX)

add_subdirectory(lib/JUCE)
add_subdirectory(lib/clap-juce-extensions)

juce_add_plugin(resize-test
    PRODUCT_NAME "ResizeTest"
    COMPANY_NAME "BaconPaul"
    BUNDLE_ID "org.baconpaul.resize-test"
    PLUGIN_MANUFACTURER_CODE BcpL
    PLUGIN_CODE RSZt

    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    
    FORMATS VST3 Standalone
)

clap_juce_extensions_plugin(TARGET resize-test
        CLAP_ID "org.baconpaul.resize-test"
        CLAP_FEATURES instrument)
add_dependencies(resize-test_All resize-test_CLAP)

target_include_directories(resize-test
  PUBLIC
  src
)

target_sources(resize-test PRIVATE
  src/PluginEditor.cpp
  src/PluginProcessor.cpp
)

target_compile_definitions(resize-test PUBLIC
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1

    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_CURL=0
    JUCE_WEB_BROWSER=0

    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0

    JUCE_ALSA=1
    JUCE_JACK=1

    DONT_SET_USING_JUCE_NAMESPACE=1
)

target_link_libraries(resize-test PRIVATE
    juce::juce_analytics
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_box2d
    juce::juce_dsp
)
