<?php

/**
 * @author Patsura Dmitry <zaets28rus@gmail.com>
 */

namespace Lynx\Tests;

class TestCase
	extends \PHPUnit_Framework_TestCase
{
    /**
     * @return string
     */
    public function getDriverName()
    {
        switch ($GLOBALS['db_type']) {
            case 'mysql':
            case 'pdo_mysql':
                return 'Mysql';
                break;
            case 'pgsql':
            case 'pdo_pgsql':
                return 'Pgsql';
                break;
            default:
                throw new \Exception('Unknown driver: ' . $GLOBALS['db_type']);
                break;
        }
    }
} 