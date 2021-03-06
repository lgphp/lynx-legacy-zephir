
extern zend_class_entry *lynx_stdlib_events_manager_ce;

ZEPHIR_INIT_CLASS(Lynx_Stdlib_Events_Manager);

PHP_METHOD(Lynx_Stdlib_Events_Manager, attach);
PHP_METHOD(Lynx_Stdlib_Events_Manager, enablePriorities);
PHP_METHOD(Lynx_Stdlib_Events_Manager, arePrioritiesEnabled);
PHP_METHOD(Lynx_Stdlib_Events_Manager, collectResponses);
PHP_METHOD(Lynx_Stdlib_Events_Manager, isCollecting);
PHP_METHOD(Lynx_Stdlib_Events_Manager, getResponses);
PHP_METHOD(Lynx_Stdlib_Events_Manager, dettachAll);
PHP_METHOD(Lynx_Stdlib_Events_Manager, fireQueue);
PHP_METHOD(Lynx_Stdlib_Events_Manager, fire);
PHP_METHOD(Lynx_Stdlib_Events_Manager, hasListeners);
PHP_METHOD(Lynx_Stdlib_Events_Manager, getListeners);

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_attach, 0, 0, 2)
	ZEND_ARG_INFO(0, eventType)
	ZEND_ARG_INFO(0, handler)
	ZEND_ARG_INFO(0, priority)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_enablepriorities, 0, 0, 1)
	ZEND_ARG_INFO(0, enablePriorities)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_collectresponses, 0, 0, 1)
	ZEND_ARG_INFO(0, collect)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_dettachall, 0, 0, 0)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_firequeue, 0, 0, 2)
	ZEND_ARG_INFO(0, queue)
	ZEND_ARG_INFO(0, event)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_fire, 0, 0, 2)
	ZEND_ARG_INFO(0, eventType)
	ZEND_ARG_INFO(0, source)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, cancelable)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_haslisteners, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_lynx_stdlib_events_manager_getlisteners, 0, 0, 1)
	ZEND_ARG_INFO(0, type)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(lynx_stdlib_events_manager_method_entry) {
	PHP_ME(Lynx_Stdlib_Events_Manager, attach, arginfo_lynx_stdlib_events_manager_attach, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, enablePriorities, arginfo_lynx_stdlib_events_manager_enablepriorities, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, arePrioritiesEnabled, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, collectResponses, arginfo_lynx_stdlib_events_manager_collectresponses, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, isCollecting, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, getResponses, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, dettachAll, arginfo_lynx_stdlib_events_manager_dettachall, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, fireQueue, arginfo_lynx_stdlib_events_manager_firequeue, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, fire, arginfo_lynx_stdlib_events_manager_fire, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, hasListeners, arginfo_lynx_stdlib_events_manager_haslisteners, ZEND_ACC_PUBLIC)
	PHP_ME(Lynx_Stdlib_Events_Manager, getListeners, arginfo_lynx_stdlib_events_manager_getlisteners, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
