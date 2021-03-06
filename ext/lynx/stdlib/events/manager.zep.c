
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "ext/spl/spl_heap.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "Zend/zend_closures.h"
#include "kernel/hash.h"
#include "kernel/string.h"
#include "kernel/concat.h"


/**
 * @author Patsura Dmitry <zaets28rus@gmail.com>
 */
ZEPHIR_INIT_CLASS(Lynx_Stdlib_Events_Manager) {

	ZEPHIR_REGISTER_CLASS(Lynx\\Stdlib\\Events, Manager, lynx, stdlib_events_manager, lynx_stdlib_events_manager_method_entry, 0);

	zend_declare_property_null(lynx_stdlib_events_manager_ce, SL("_events"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(lynx_stdlib_events_manager_ce, SL("_collect"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(lynx_stdlib_events_manager_ce, SL("_enablePriorities"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(lynx_stdlib_events_manager_ce, SL("_responses"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_class_implements(lynx_stdlib_events_manager_ce TSRMLS_CC, 1, lynx_stdlib_events_eventsmanager_ce);
	return SUCCESS;

}

/**
 * Attach a listener to the events manager
 *
 * @param string eventType
 * @param object handler
 * @param int priority
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, attach) {

	int priority, ZEPHIR_LAST_CALL_STATUS;
	zval *eventType_param = NULL, *handler, *priority_param = NULL, *priorityQueue = NULL, *events = NULL, *_0, *_1 = NULL;
	zval *eventType = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &eventType_param, &handler, &priority_param);

	if (unlikely(Z_TYPE_P(eventType_param) != IS_STRING && Z_TYPE_P(eventType_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'eventType' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(eventType_param) == IS_STRING)) {
		zephir_get_strval(eventType, eventType_param);
	} else {
		ZEPHIR_INIT_VAR(eventType);
		ZVAL_EMPTY_STRING(eventType);
	}
	if (!priority_param) {
		priority = 100;
	} else {
	if (unlikely(Z_TYPE_P(priority_param) != IS_LONG)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'priority' must be a long/integer") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	priority = Z_LVAL_P(priority_param);
	}


	if (Z_TYPE_P(handler) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "Event handler must be an Object", "lynx/Stdlib/Events/Manager.zep", 29);
		return;
	}
	ZEPHIR_OBS_VAR(events);
	zephir_read_property_this(&events, this_ptr, SL("_events"), PH_NOISY_CC);
	if (Z_TYPE_P(events) != IS_ARRAY) {
		ZEPHIR_INIT_NVAR(events);
		array_init(events);
	}
	ZEPHIR_OBS_VAR(priorityQueue);
	if (zephir_array_isset_fetch(&priorityQueue, events, eventType, 0 TSRMLS_CC)) {
		_0 = zephir_fetch_nproperty_this(this_ptr, SL("_enablePriorities"), PH_NOISY_CC);
		ZEPHIR_INIT_NVAR(priorityQueue);
		if (zephir_is_true(_0)) {
			object_init_ex(priorityQueue, spl_ce_SplPriorityQueue);
			if (zephir_has_constructor(priorityQueue TSRMLS_CC)) {
				ZEPHIR_CALL_METHOD(NULL, priorityQueue, "__construct", NULL);
				zephir_check_call_status();
			}
			ZEPHIR_INIT_VAR(_1);
			ZVAL_LONG(_1, 1);
			ZEPHIR_CALL_METHOD(NULL, priorityQueue, "setextractflags", NULL, _1);
			zephir_check_call_status();
			zephir_array_update_zval(&events, eventType, &priorityQueue, PH_COPY | PH_SEPARATE);
			zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
		} else {
			array_init(priorityQueue);
		}
	} else {
		ZEPHIR_INIT_NVAR(priorityQueue);
		array_init(priorityQueue);
	}
	if (Z_TYPE_P(priorityQueue) == IS_OBJECT) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_LONG(_1, priority);
		ZEPHIR_CALL_METHOD(NULL, priorityQueue, "insert", NULL, handler, _1);
		zephir_check_call_status();
	} else {
		zephir_array_append(&priorityQueue, handler, PH_SEPARATE, "lynx/Stdlib/Events/Manager.zep", 76);
		zephir_array_update_zval(&events, eventType, &priorityQueue, PH_COPY | PH_SEPARATE);
		zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Set if priorities are enabled in the EventsManager
 *
 * @param boolean enablePriorities
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, enablePriorities) {

	zval *enablePriorities_param = NULL;
	zend_bool enablePriorities;

	zephir_fetch_params(0, 1, 0, &enablePriorities_param);

	enablePriorities = zephir_get_boolval(enablePriorities_param);


	zephir_update_property_this(this_ptr, SL("_enablePriorities"), enablePriorities ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

/**
 * Returns if priorities are enabled
 *
 * @return boolean
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, arePrioritiesEnabled) {


	RETURN_MEMBER(this_ptr, "_enablePriorities");

}

/**
 * Tells the event manager if it needs to collect all the responses returned by every
 * registered listener in a single fire
 *
 * @param boolean collect
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, collectResponses) {

	zval *collect_param = NULL;
	zend_bool collect;

	zephir_fetch_params(0, 1, 0, &collect_param);

	collect = zephir_get_boolval(collect_param);


	zephir_update_property_this(this_ptr, SL("_collect"), collect ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false) TSRMLS_CC);

}

/**
 * Check if the events manager is collecting all all the responses returned by every
 * registered listener in a single fire
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, isCollecting) {


	RETURN_MEMBER(this_ptr, "_collect");

}

/**
 * Returns all the responses returned by every handler executed by the last 'fire' executed
 *
 * @return array
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, getResponses) {


	RETURN_MEMBER(this_ptr, "_responses");

}

/**
 * Removes all events from the EventsManager
 *
 * @param string type
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, dettachAll) {

	zval *type_param = NULL, *events = NULL;
	zval *type = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &type_param);

	if (!type_param) {
		ZEPHIR_INIT_VAR(type);
		ZVAL_EMPTY_STRING(type);
	} else {
		zephir_get_strval(type, type_param);
	}


	ZEPHIR_OBS_VAR(events);
	zephir_read_property_this(&events, this_ptr, SL("_events"), PH_NOISY_CC);
	if (ZEPHIR_IS_STRING_IDENTICAL(type, "")) {
		ZEPHIR_INIT_NVAR(events);
		ZVAL_NULL(events);
	} else {
		if (zephir_array_isset(events, type)) {
			zephir_array_update_zval(&events, type, &ZEPHIR_GLOBAL(global_null), PH_COPY | PH_SEPARATE);
		}
	}
	zephir_update_property_this(this_ptr, SL("_events"), events TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Internal handler to call a queue of events
 *
 * @param \SplPriorityQueue|array queue
 * @param Phalcon\Events\Event event
 * @return mixed
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, fireQueue) {

	HashTable *_6;
	HashPosition _5;
	zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool collect, cancelable, _0;
	zval *queue, *event, *status = NULL, *arguments = NULL, *eventName = NULL, *data = NULL, *iterator, *source = NULL, *handler = NULL, *_1 = NULL, *_2, *_4 = NULL, **_7;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &queue, &event);



	_0 = Z_TYPE_P(queue) != IS_ARRAY;
	if (_0) {
		_0 = Z_TYPE_P(queue) != IS_OBJECT;
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "The queue is not valid", "lynx/Stdlib/Events/Manager.zep", 165);
		return;
	}
	if (Z_TYPE_P(event) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "The event is not valid", "lynx/Stdlib/Events/Manager.zep", 169);
		return;
	}
	ZEPHIR_INIT_VAR(status);
	ZVAL_NULL(status);
	ZEPHIR_INIT_VAR(arguments);
	ZVAL_NULL(arguments);
	ZEPHIR_CALL_METHOD(&eventName, event, "gettype", NULL);
	zephir_check_call_status();
	if (Z_TYPE_P(eventName) != IS_STRING) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(zend_exception_get_default(TSRMLS_C), "The event type not valid", "lynx/Stdlib/Events/Manager.zep", 179);
		return;
	}
	ZEPHIR_CALL_METHOD(&source, event, "getsource", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&data, event, "getdata", NULL);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, event, "getcancelable", NULL);
	zephir_check_call_status();
	cancelable = zephir_get_boolval(_1);
	ZEPHIR_OBS_VAR(_2);
	zephir_read_property_this(&_2, this_ptr, SL("_collect"), PH_NOISY_CC);
	collect = zephir_get_boolval(_2);
	if (ZEPHIR_IS_STRING(queue, "object")) {
		ZEPHIR_INIT_VAR(iterator);
		if (zephir_clone(iterator, queue TSRMLS_CC) == FAILURE) {
			RETURN_MM();
		}
		ZEPHIR_CALL_METHOD(NULL, iterator, "top", NULL);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_1, iterator, "valid", NULL);
			zephir_check_call_status();
			if (!(zephir_is_true(_1))) {
				break;
			}
			ZEPHIR_CALL_METHOD(&handler, iterator, "current", &_3);
			zephir_check_call_status();
			if (Z_TYPE_P(handler) == IS_OBJECT) {
				if (zephir_instance_of_ev(handler, zend_ce_closure TSRMLS_CC)) {
					if (Z_TYPE_P(arguments) == IS_NULL) {
						ZEPHIR_INIT_NVAR(arguments);
						array_init_size(arguments, 5);
						zephir_array_fast_append(arguments, event);
						zephir_array_fast_append(arguments, source);
						zephir_array_fast_append(arguments, data);
					}
					ZEPHIR_INIT_NVAR(status);
					ZEPHIR_CALL_USER_FUNC_ARRAY(status, handler, arguments);
					zephir_check_call_status();
					if (collect) {
						zephir_update_property_array_append(this_ptr, SL("_responses"), status TSRMLS_CC);
					}
					if (cancelable) {
						ZEPHIR_CALL_METHOD(&_4, event, "isstopped", NULL);
						zephir_check_call_status();
						if (zephir_is_true(_4)) {
							break;
						}
					}
				} else {
					if ((zephir_method_exists(handler, eventName TSRMLS_CC)  == SUCCESS)) {
						ZEPHIR_CALL_METHOD_ZVAL(&status, handler, eventName, NULL, event, source, data);
						zephir_check_call_status();
						if (collect) {
							zephir_update_property_array_append(this_ptr, SL("_responses"), status TSRMLS_CC);
						}
						if (cancelable) {
							ZEPHIR_CALL_METHOD(&_4, event, "isstopped", NULL);
							zephir_check_call_status();
							if (zephir_is_true(_4)) {
								break;
							}
						}
					}
				}
			}
		}
	} else {
		zephir_is_iterable(queue, &_6, &_5, 0, 0, "lynx/Stdlib/Events/Manager.zep", 373);
		for (
		  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
		  ; zephir_hash_move_forward_ex(_6, &_5)
		) {
			ZEPHIR_GET_HVALUE(handler, _7);
			if (Z_TYPE_P(handler) == IS_OBJECT) {
				if (zephir_instance_of_ev(handler, zend_ce_closure TSRMLS_CC)) {
					if (Z_TYPE_P(arguments) == IS_NULL) {
						ZEPHIR_INIT_NVAR(arguments);
						array_init_size(arguments, 5);
						zephir_array_fast_append(arguments, event);
						zephir_array_fast_append(arguments, source);
						zephir_array_fast_append(arguments, data);
					}
					ZEPHIR_INIT_NVAR(status);
					ZEPHIR_CALL_USER_FUNC_ARRAY(status, handler, arguments);
					zephir_check_call_status();
					if (collect) {
						zephir_update_property_array_append(this_ptr, SL("_responses"), status TSRMLS_CC);
					}
					if (cancelable) {
						ZEPHIR_CALL_METHOD(&_4, event, "isstopped", NULL);
						zephir_check_call_status();
						if (zephir_is_true(_4)) {
							break;
						}
					}
				} else {
					if ((zephir_method_exists(handler, eventName TSRMLS_CC)  == SUCCESS)) {
						ZEPHIR_CALL_METHOD_ZVAL(&status, handler, eventName, NULL, event, source, data);
						zephir_check_call_status();
						if (collect) {
							zephir_update_property_array_append(this_ptr, SL("_responses"), status TSRMLS_CC);
						}
						if (cancelable) {
							ZEPHIR_CALL_METHOD(&_4, event, "isstopped", NULL);
							zephir_check_call_status();
							if (zephir_is_true(_4)) {
								break;
							}
						}
					}
				}
			}
		}
	}
	RETURN_CCTOR(status);

}

/**
 * Fires an event in the events manager causing that active listeners be notified about it
 *
 *<code>
 *  $eventsManager->fire('db', $connection);
 *</code>
 *
 * @param string eventType
 * @param object source
 * @param mixed  data
 * @param boolean cancelable
 * @return mixed
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, fire) {

	zephir_fcall_cache_entry *_4 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool cancelable, _3;
	zval *eventType_param = NULL, *source, *data = NULL, *cancelable_param = NULL, *events, *eventParts, *type, *eventName, *event = NULL, *status = NULL, *fireEvents = NULL, *_0, *_2;
	zval *eventType = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &eventType_param, &source, &data, &cancelable_param);

	if (unlikely(Z_TYPE_P(eventType_param) != IS_STRING && Z_TYPE_P(eventType_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'eventType' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(eventType_param) == IS_STRING)) {
		zephir_get_strval(eventType, eventType_param);
	} else {
		ZEPHIR_INIT_VAR(eventType);
		ZVAL_EMPTY_STRING(eventType);
	}
	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}
	if (!cancelable_param) {
		cancelable = 1;
	} else {
		cancelable = zephir_get_boolval(cancelable_param);
	}


	ZEPHIR_OBS_VAR(events);
	zephir_read_property_this(&events, this_ptr, SL("_events"), PH_NOISY_CC);
	if (Z_TYPE_P(events) != IS_ARRAY) {
		RETURN_MM_NULL();
	}
	if (!(zephir_memnstr_str(eventType, SL(":"), "lynx/Stdlib/Events/Manager.zep", 403))) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, zend_exception_get_default(TSRMLS_C));
		ZEPHIR_INIT_VAR(_1);
		ZEPHIR_CONCAT_SV(_1, "Invalid event type ", eventType);
		ZEPHIR_CALL_METHOD(NULL, _0, "__construct", NULL, _1);
		zephir_check_call_status();
		zephir_throw_exception_debug(_0, "lynx/Stdlib/Events/Manager.zep", 404 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(eventParts);
	zephir_fast_explode_str(eventParts, SL(":"), eventType, LONG_MAX TSRMLS_CC);
	ZEPHIR_OBS_VAR(type);
	zephir_array_fetch_long(&type, eventParts, 0, PH_NOISY, "lynx/Stdlib/Events/Manager.zep", 408 TSRMLS_CC);
	ZEPHIR_OBS_VAR(eventName);
	zephir_array_fetch_long(&eventName, eventParts, 1, PH_NOISY, "lynx/Stdlib/Events/Manager.zep", 409 TSRMLS_CC);
	ZEPHIR_INIT_VAR(status);
	ZVAL_NULL(status);
	_2 = zephir_fetch_nproperty_this(this_ptr, SL("_collect"), PH_NOISY_CC);
	if (zephir_is_true(_2)) {
		zephir_update_property_this(this_ptr, SL("_responses"), ZEPHIR_GLOBAL(global_null) TSRMLS_CC);
	}
	ZEPHIR_INIT_VAR(event);
	ZVAL_NULL(event);
	ZEPHIR_OBS_VAR(fireEvents);
	if (zephir_array_isset_fetch(&fireEvents, events, type, 0 TSRMLS_CC)) {
		_3 = Z_TYPE_P(fireEvents) == IS_OBJECT;
		if (!(_3)) {
			_3 = Z_TYPE_P(fireEvents) == IS_ARRAY;
		}
		if (_3) {
			ZEPHIR_INIT_NVAR(event);
			object_init_ex(event, lynx_stdlib_events_event_ce);
			ZEPHIR_CALL_METHOD(NULL, event, "__construct", &_4, eventName, source, data, (cancelable ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&status, this_ptr, "firequeue", NULL, fireEvents, event);
			zephir_check_call_status();
		}
	}
	ZEPHIR_OBS_NVAR(fireEvents);
	if (zephir_array_isset_fetch(&fireEvents, events, eventType, 0 TSRMLS_CC)) {
		_3 = Z_TYPE_P(fireEvents) == IS_OBJECT;
		if (!(_3)) {
			_3 = Z_TYPE_P(fireEvents) == IS_ARRAY;
		}
		if (_3) {
			if (Z_TYPE_P(event) == IS_NULL) {
				ZEPHIR_INIT_NVAR(event);
				object_init_ex(event, lynx_stdlib_events_event_ce);
				ZEPHIR_CALL_METHOD(NULL, event, "__construct", &_4, eventName, source, data, (cancelable ? ZEPHIR_GLOBAL(global_true) : ZEPHIR_GLOBAL(global_false)));
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&status, this_ptr, "firequeue", NULL, fireEvents, event);
			zephir_check_call_status();
		}
	}
	RETURN_CCTOR(status);

}

/**
 * Check whether certain type of event has listeners
 *
 * @param string type
 * @return boolean
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, hasListeners) {

	zval *type_param = NULL, *_0;
	zval *type = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &type_param);

	if (unlikely(Z_TYPE_P(type_param) != IS_STRING && Z_TYPE_P(type_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'type' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(type_param) == IS_STRING)) {
		zephir_get_strval(type, type_param);
	} else {
		ZEPHIR_INIT_VAR(type);
		ZVAL_EMPTY_STRING(type);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
	RETURN_MM_BOOL(zephir_array_isset(_0, type));

}

/**
 * Returns all the attached listeners of a certain type
 *
 * @param string type
 * @return array
 */
PHP_METHOD(Lynx_Stdlib_Events_Manager, getListeners) {

	zval *type_param = NULL, *events, *fireEvents;
	zval *type = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &type_param);

	if (unlikely(Z_TYPE_P(type_param) != IS_STRING && Z_TYPE_P(type_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'type' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (likely(Z_TYPE_P(type_param) == IS_STRING)) {
		zephir_get_strval(type, type_param);
	} else {
		ZEPHIR_INIT_VAR(type);
		ZVAL_EMPTY_STRING(type);
	}


	events = zephir_fetch_nproperty_this(this_ptr, SL("_events"), PH_NOISY_CC);
	if (Z_TYPE_P(events) == IS_ARRAY) {
		if (zephir_array_isset_fetch(&fireEvents, events, type, 1 TSRMLS_CC)) {
			RETURN_CTOR(fireEvents);
		}
	}
	array_init(return_value);
	RETURN_MM();

}

