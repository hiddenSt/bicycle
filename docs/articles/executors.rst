Executors
=========

This documents describes *executor* abstraction. The main API is function ``Submit``

.. code:: c++

   void Submit(Task* task);

This function provide *fire-and-forget*-style interface. It accepts a single nullary invocable
which is represented as ``task`` parameter of type ``Task``.

Executor abstracts resources where tasks physically executes. Underlying resource may
be a ``StaticThreadPool`` or ``InlineExecutor``. The following executors are supported:

- ``StaticThreadPool``
- ``InlineExecutor``
- ``ManualExecutor``
- ``Strand``
