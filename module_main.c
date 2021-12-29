#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "hashbox.h" 

static PyObject*
dwh_hashkit_check(PyObject *self, PyObject *args) {
  const char* data;
  Py_ssize_t len;

  if (!PyArg_ParseTuple(args, "s#", &data, &len))
    return NULL;

  hashbox_t* hashbox = hashbox_new();
  hashbox_update(hashbox, data, len);
  unsigned int result = hashbox_final(hashbox);

  return Py_BuildValue("i", result);
}

static PyObject*
dwh_hashkit_hash(PyObject *self, PyObject *args) {
  unsigned char* data;
  Py_ssize_t len;

  if (!PyArg_ParseTuple(args, "s#", &data, &len))
    return NULL;

  // hash the string
  hashbox_t* hashbox = hashbox_new();
  hashbox_update(hashbox, data, len);
  unsigned char ** result = hashbox_hash(hashbox);
  // create a python list to store the hashes in
  PyObject* list = PyList_New(18);
  // iterate the hashes
  for (int i=0; i<18; i++) {
    PyObject* item = PyBytes_FromStringAndSize(result[i], sizeof(uint8_t) * 64);
    // store the string in the list
    PyList_SetItem(list, i, item);
    // memory bleh
    //Py_DECREF(item);
    //free(result[i]);
  }
  free(result);
  return list;
}

static PyMethodDef dwh_hashkit_methods[] = {
     {"check", dwh_hashkit_check, METH_VARARGS, "Checks if an input hashes to the deep web hash"},
     {"hash", dwh_hashkit_hash, METH_VARARGS, "Returns the hashed value of a string from every 512 bit hash"},
     {NULL, NULL, 0, NULL}
};

static struct PyModuleDef dwh_hashkit_module =
{
    PyModuleDef_HEAD_INIT,
    "dwh_hashkit",
    NULL,
    -1,
    dwh_hashkit_methods
};

PyMODINIT_FUNC
PyInit_dwh_hashkit(void) {
     return PyModule_Create(&dwh_hashkit_module);
}
