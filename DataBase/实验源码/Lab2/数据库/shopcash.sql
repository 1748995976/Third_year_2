/*
 Navicat MySQL Data Transfer

 Source Server         : Local instance MySQL
 Source Server Type    : MySQL
 Source Server Version : 80017
 Source Host           : localhost:3306
 Source Schema         : shopcash

 Target Server Type    : MySQL
 Target Server Version : 80017
 File Encoding         : 65001

 Date: 24/06/2020 09:20:22
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for chargerecord
-- ----------------------------
DROP TABLE IF EXISTS `chargerecord`;
CREATE TABLE `chargerecord`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `jobid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `cdate` date NULL DEFAULT NULL,
  `chargeamount` double NULL DEFAULT NULL,
  `vipid` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `jobid`(`jobid`) USING BTREE,
  CONSTRAINT `chargerecord_ibfk_1` FOREIGN KEY (`jobid`) REFERENCES `employee` (`jobid`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of chargerecord
-- ----------------------------
INSERT INTO `chargerecord` VALUES (1, 'root', '2020-05-26', 1000, NULL);
INSERT INTO `chargerecord` VALUES (2, 'root', '2020-05-26', 1000, NULL);
INSERT INTO `chargerecord` VALUES (3, 'root', '2020-05-26', 630, 2);

-- ----------------------------
-- Table structure for employee
-- ----------------------------
DROP TABLE IF EXISTS `employee`;
CREATE TABLE `employee`  (
  `jobid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ename` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `phone` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `passwd` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`jobid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of employee
-- ----------------------------
INSERT INTO `employee` VALUES ('root', '王占成', '11111111111', '123456');

-- ----------------------------
-- Table structure for expenserecord
-- ----------------------------
DROP TABLE IF EXISTS `expenserecord`;
CREATE TABLE `expenserecord`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `vipid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `edate` date NULL DEFAULT NULL,
  `monetary` double NULL DEFAULT NULL,
  `goodid` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `goodnumber` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `vipid`(`vipid`) USING BTREE,
  CONSTRAINT `expenserecord_ibfk_1` FOREIGN KEY (`vipid`) REFERENCES `vip` (`vipid`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 3 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of expenserecord
-- ----------------------------
INSERT INTO `expenserecord` VALUES (1, NULL, '2020-05-26', 1000, '00001', 100);
INSERT INTO `expenserecord` VALUES (2, NULL, '2020-05-26', 1000, '00001', 100);
INSERT INTO `expenserecord` VALUES (3, '2', '2020-05-26', 630, '00001', 70);

-- ----------------------------
-- Table structure for goods
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods`  (
  `productcode` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `remainingnumber` int(11) NULL DEFAULT NULL,
  `price` double NULL DEFAULT NULL,
  `ganme` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`productcode`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('00001', 1730, 10, '小橘子');
INSERT INTO `goods` VALUES ('00002', 2000, 10, '小苹果果');
INSERT INTO `goods` VALUES ('00003', 2000, 5, '小西红柿');

-- ----------------------------
-- Table structure for super
-- ----------------------------
DROP TABLE IF EXISTS `super`;
CREATE TABLE `super`  (
  `superid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sname` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `phone` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `passwd` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`superid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of super
-- ----------------------------
INSERT INTO `super` VALUES ('root', '王占成', '11111111111', '654321');

-- ----------------------------
-- Table structure for vip
-- ----------------------------
DROP TABLE IF EXISTS `vip`;
CREATE TABLE `vip`  (
  `vipid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `expense` double NULL DEFAULT NULL,
  `state` smallint(6) NULL DEFAULT NULL,
  `pd` date NULL DEFAULT NULL,
  `exp` date NULL DEFAULT NULL,
  PRIMARY KEY (`vipid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of vip
-- ----------------------------
INSERT INTO `vip` VALUES ('1', 0, 0, '2020-05-26', NULL);
INSERT INTO `vip` VALUES ('2', 700, 0, '2020-05-26', '2021-05-26');

SET FOREIGN_KEY_CHECKS = 1;
