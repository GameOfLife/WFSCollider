if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/nova-simd/vec.hpp)
	message(FATAL_ERROR "nova-simd submodule is missing: please run `git submodule init && git submodule update' from the toplevel of your git working tree")
endif()

if(NOT Boost_FOUND) # we compile boost ourselves
	# boost thread
	aux_source_directory(boost/libs/thread/src/ boost_thread_src )

	include_directories(boost)

	if(WIN32)
		aux_source_directory(boost/libs/thread/src/win32/ boost_thread_platform )
		add_definitions(-DBOOST_THREAD_BUILD_LIB)
	elseif(PTHREADS_FOUND)
		aux_source_directory(boost/libs/thread/src/pthread/ boost_thread_platform )
	else()
		message(SEND_ERROR "we need to implement boost_thread")
	endif()

	include_directories(${PTHREADS_INCLUDE_DIR})

	if (SUPERNOVA)
		aux_source_directory(boost/libs/program_options/src/ boost_program_options )
		add_library(boost_program_options STATIC ${boost_program_options})

		aux_source_directory(boost/libs/system/src/ boost_system )
		add_library(boost_system STATIC ${boost_system})

		aux_source_directory(boost/libs/filesystem/v3/src boost_filesystem_v3)
		add_library(boost_filesystem STATIC ${boost_filesystem_v2} ${boost_filesystem_v3})

		if(LTO)
			set_property(TARGET boost_program_options boost_system boost_filesystem
						 APPEND PROPERTY COMPILE_FLAGS "-flto -flto-report")

			set_property(TARGET boost_program_options boost_system boost_filesystem
						 APPEND PROPERTY LINK_FLAGS "-flto -flto-report")
		endif()
	endif()

	if (${DSO_VISIBILITY})
		remove_definitions(-fvisibility=hidden)
	endif()

	add_library(boost_thread STATIC ${boost_thread_src} ${boost_thread_platform})

	if(LTO)
		set_property(TARGET boost_thread
					APPEND PROPERTY COMPILE_FLAGS "-flto -flto-report")

		set_property(TARGET boost_thread
					APPEND PROPERTY LINK_FLAGS "-flto -flto-report")
	endif()
endif()

if (SUPERNOVA)
	#oscpack
	add_library(oscpack STATIC "oscpack_build.cpp")

	#tlsf
	add_library(tlsf STATIC "TLSF-2.4.6/src/tlsf.c")
	set_target_properties(tlsf
						 PROPERTIES COMPILE_DEFINITIONS TLSF_STATISTIC=1)
	if(LTO)
		set_property(TARGET oscpack tlsf
					 APPEND PROPERTY COMPILE_FLAGS "-flto -flto-report")

		set_property(TARGET oscpack tlsf
					 APPEND PROPERTY LINK_FLAGS "-flto -flto-report")
	endif()
endif()

