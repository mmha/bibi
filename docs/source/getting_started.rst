===============
Getting Started
===============

------------------
What are Concepts?
------------------
Take a look at `this presentation by Andrew Sutton <https://github.com/CppCon/CppCon2014/tree/master/Presentations/Generic%20Programming%20with%20Concepts%20Lite>`_.

-------------------------------------------
Where can I find the C++ Standard Concepts?
-------------------------------------------
Most of them can be found on `cppreference <http://en.cppreference.com/w/cpp/concept>`_. Those missing can still be found in the C++ working draft, which is avaliable for free.

-------------------------------------------
How do I include this library in my Project?
-------------------------------------------

Don't forget to enable the C++17 and Concepts TS support in your compiler (:code:`-std=c++1z -fconcepts` in the case of gcc).

Quick and Dirty
---------------
Copy the contents of the `include` directory into your project.

Using CMake (in-tree)
---------------------
:code:`add_subdirectory()` bibis root and link against the bibi::bibi target.

Using CMake (out-of-tree)
-------------------------
You can install the library:

.. code-block:: bash

	mkdir bibi/build
	cd bibi/build
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	sudo make install
	# Alternatively, on Arch Linux:
	cd bibi
	makepkg -si

Then you can use :code:`find_package(bibi)` in your Project:

.. code-block:: cmake

	find_package(bibi REQUIRED)
	add_executable(mars_climate_orbiter main.cpp)
	target_link_libraries(mars_climate_orbiter PRIVATE bibi::bibi)
	# Note that -std=foo might interfere with CMAKE_CXX_STANDARD, unfortunately CMake does not support C++1z/C++17 by itself
	target_compile_options(mars_climate_orbiter PRIVATE -std=c++1z)

------------------------
Structure of the Library
------------------------
All files are located in the `bibi` directory. The namespaces try to resemble those of the standard library, so all concepts can be found in the :code:`bibi` namespace, the exception being :code:`bibi::chrono` containing :code:`Clock` and :code:`TrivialClock`.