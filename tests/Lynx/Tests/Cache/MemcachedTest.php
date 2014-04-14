<?php
/**
 * @author Patsura Dmitry <zaets28rus@gmail.com>
 */

namespace Lynx\Tests\Cache;

class MemcachedTest
    extends TestCase
{
	protected function initCacheDriver()
	{
		$driver = new \Lynx\Cache\Memcache();
		return $driver;
	}
} 