
extern zend_class_entry *lynx_dbal_connection_ce;

ZEPHIR_INIT_CLASS(Lynx_DBAL_Connection);

PHP_METHOD(Lynx_DBAL_Connection, getDriver);
PHP_METHOD(Lynx_DBAL_Connection, __construct);
PHP_METHOD(Lynx_DBAL_Connection, insert);
PHP_METHOD(Lynx_DBAL_Connection, update);
PHP_METHOD(Lynx_DBAL_Connection, deleteByColumn);
PHP_METHOD(Lynx_DBAL_Connection, delete);
PHP_METHOD(Lynx_DBAL_Connection, prepare);

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, parameters)
	ZEND_ARG_OBJ_INFO(0, eventsManager, Lynx\\Stdlib\\Events\\Manager, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection_insert, 0, 0, 2)
	ZEND_ARG_INFO(0, table)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
	ZEND_ARG_ARRAY_INFO(0, types, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection_update, 0, 0, 3)
	ZEND_ARG_INFO(0, table)
	ZEND_ARG_ARRAY_INFO(0, data, 0)
	ZEND_ARG_ARRAY_INFO(0, identifiers, 0)
	ZEND_ARG_ARRAY_INFO(0, types, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection_deletebycolumn, 0, 0, 3)
	ZEND_ARG_INFO(0, table)
	ZEND_ARG_INFO(0, column)
	ZEND_ARG_INFO(0, value)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection_delete, 0, 0, 2)
	ZEND_ARG_INFO(0, table)
	ZEND_ARG_ARRAY_INFO(0, identifiers, 0)
	ZEND_ARG_ARRAY_INFO(0, types, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_dbal_connection_prepare, 0, 0, 1)
	ZEND_ARG_INFO(0, statement)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(lynx_dbal_connection_method_entry) {
	PHP_ME(Lynx_DBAL_Connection, getDriver, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_DBAL_Connection, __construct, arginfo_lynx_dbal_connection___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Lynx_DBAL_Connection, insert, arginfo_lynx_dbal_connection_insert, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_DBAL_Connection, update, arginfo_lynx_dbal_connection_update, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_DBAL_Connection, deleteByColumn, arginfo_lynx_dbal_connection_deletebycolumn, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_DBAL_Connection, delete, arginfo_lynx_dbal_connection_delete, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_DBAL_Connection, prepare, arginfo_lynx_dbal_connection_prepare, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
