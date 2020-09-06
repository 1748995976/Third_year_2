-- 下面是会员信息
-- pd：办卡日期
-- state=0：该会员卡长期有效
-- state=1：该会员卡当前有效，截止日期为exp
-- state=2：该会员卡无效
CREATE TABLE vip(
	vipid CHAR(10),
	expense DOUBLE,
	state SMALLINT,
	pd date,
	exp date,
	PRIMARY KEY (vipid)
	);
-- 下面是消费记录
-- id：消费流水号
-- edate：消费日期
-- monetary：消费金额
CREATE TABLE expenserecord(
	id INT,
	vipid CHAR(10),
	edate date,
	monetary DOUBLE,
	goodid CHAR(20),
	goodnumber INT,
	PRIMARY KEY (id),
	FOREIGN KEY (vipid) REFERENCES vip(vipid)
	);
ALTER TABLE expenserecord
MODIFY COLUMN id INT NOT NULL AUTO_INCREMENT FIRST;
-- 下面是收银员信息
CREATE TABLE employee(
	jobid CHAR(10),
	ename CHAR(10),
	phone CHAR(20),
	passwd CHAR(6),
	PRIMARY KEY (jobid)
	);
-- 下面是款项盘存
-- id：收费流水号
-- jobid：工号
-- cdate：收费日期
-- chargeamount：收费金额
CREATE TABLE chargerecord(
	id INT,
	jobid CHAR(10) NOT NULL,
	cdate date,
	chargeamount DOUBLE,
	vipid INT,
	PRIMARY KEY (id),
	FOREIGN KEY (jobid) REFERENCES employee(jobid)
	);
ALTER TABLE chargerecord
MODIFY COLUMN id INT NOT NULL AUTO_INCREMENT FIRST;
-- 下面是商品信息
CREATE TABLE goods(
	productcode CHAR(20),
	remainingnumber INT,
	price DOUBLE,
	ganme CHAR(20),
	PRIMARY KEY (productcode)
	);


CREATE TABLE super(
	superid CHAR(10),
	sname CHAR(10),
	phone CHAR(20),
	passwd CHAR(6),
	PRIMARY KEY (superid)
	);
	
-- 	ALTER TABLE `shopcash`.`expenserecord` 
-- MODIFY COLUMN `vipid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL AFTER `id`;