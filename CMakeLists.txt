cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11 CACHE STRING "Build for 10.11")

project(toy-juce VERSION 0.9.0 LANGUAGES CXX)

add_subdirectory(lib/JUCE)

set( BUILD_VST2 FALSE )
if( BUILD_VST2 )
    set( EXTRA_FORMATS VST )
    juce_set_vst2_sdk_path( "../VST2_SDK")
else()
    set( EXTRA_FORMATS "" )
endif()

message( STATUS "Extra Formats : ${EXTRA_FORMATS}" )

juce_add_plugin(toy-juce
    PRODUCT_NAME "ToyJuce"
    COMPANY_NAME "Surge Synth Team"  
    BUNDLE_ID "org.surge-synth-team.toy-juce"
    PLUGIN_MANUFACTURER_CODE VmbA
    PLUGIN_CODE ToJC

    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    
    FORMATS AU VST3 Standalone ${EXTRA_FORMATS}
)

juce_generate_juce_header( toy-juce )

target_include_directories(toy-juce 
  PUBLIC
  src
)

target_sources(toy-juce PRIVATE
  src/PluginEditor.cpp
  src/PluginProcessor.cpp
)

target_compile_definitions(toy-juce PUBLIC
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

target_link_libraries(toy-juce PRIVATE
    juce::juce_analytics
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_blocks_basics
    juce::juce_box2d
    juce::juce_dsp
)
