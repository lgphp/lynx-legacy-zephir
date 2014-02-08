
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"


/**
 * @author Patsura Dmitry <zaets28rus@gmail.com>
 */
ZEPHIR_INIT_CLASS(Phalcon_ORM_UnitOfWork) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\ORM, UnitOfWork, phalcon, orm_unitofwork, phalcon_orm_unitofwork_method_entry, 0);

	zend_declare_property_null(phalcon_orm_unitofwork_ce, SL("em"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Phalcon_ORM_UnitOfWork, __construct) {

	zval *em;

	zephir_fetch_params(0, 1, 0, &em);



	zephir_update_property_this(this_ptr, SL("em"), em TSRMLS_CC);

}
