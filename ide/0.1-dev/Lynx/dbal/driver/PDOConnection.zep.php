<?php

namespace Lynx\DBAL\Driver;

class PDOConnection
{

    protected $eventsManager;


    protected $dsn;


    protected $username;


    protected $password;


    protected $driverOptions;


    protected $connection;


    /**
     * @param mixed $eventsManager 
     */
	public function setEventsManager($eventsManager) {}


	public function getEventsManager() {}

    /**
     * @param string $dsn 
     * @param mixed $username 
     * @param mixed $password 
     * @param array $driverOptions 
     */
	public function __construct($dsn, $username = null, $password = null, $driverOptions = array()) {}

    /**
     * @return bool 
     */
	public function isConnected() {}

    /**
     * Execute query and return result
     *
     * @param string $query 
     * @return int 
     */
	public function execute($query) {}


	public function connect() {}


	public function lastInsertId() {}

    /**
     * @param mixed $statement 
     */
	public function prepare($statement) {}

}
