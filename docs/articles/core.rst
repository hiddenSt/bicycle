Core
====

Core module contains types, which must be used to keep up with library coding conventions.

The following contains the macro to improve code readability:

The basic macro allows to panic in the case of unexpected condition

.. doxygendefine:: BICYCLE_PANIC

Use this in case where your code

Contracts
---------

Many languages has contracts, which allows to add check function invariants.
As C++ 20 standard, we do not have language-level support fot contracts. As a replacement
we use macros, which calls `std::abort` in case of condition failure.

The first is pre-condition contract:

.. doxygendefine:: BICYCLE_EXPECTS


.. doxygendefine:: BICYCLE_ENSURES

Unreachable code paths
----------------------

Consider the following example:

.. code-block:: c++
   :linenos:

   enum Type {
     kVal_1,
     kVal_2,
   };

   switch (type) {
    case Type::kVal_1:
    break;
    case Type::kVal_2:
    break;
    default:
     BICYCLE_UNREACHABLE();
   }


So to ensure

.. doxygendefine:: BICYCLE_UNREACHABLE

To represent the return value of an operation expected to fail use the following class template:

.. doxygenfile:: core/include/bicycle/core/result.hpp