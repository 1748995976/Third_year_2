-- 查询1
SELECT taketrainrecord.RID,taketrainrecord.PCardID,taketrainrecord.TID,taketrainrecord.SStationID,taketrainrecord.AStationID,CarrigeID,SeatRow,SeatNo,SStatus
FROM taketrainrecord,diagnoserecord,train,passenger
WHERE taketrainrecord.PCardID = diagnoserecord.PCardID
AND taketrainrecord.PCardID = passenger.PCardID
AND taketrainrecord.TID = train.TID
AND passenger.PName = '李玉兰'
AND DATEDIFF(train.SDate,diagnoserecord.FDay) <= 14;
-- 查询2
SELECT s2.CityName
FROM taketrainrecord,station s1,station s2
WHERE s1.SID = taketrainrecord.SStationID
AND s2.SID = taketrainrecord.AStationID
AND s1.CityName = '武汉'
-- 查询3
SELECT DATEDIFF(diagnoserecord.DDay,diagnoserecord.FDay),passenger.PCardID,PName,Age,Sex
FROM diagnoserecord,passenger
WHERE diagnoserecord.PCardID = passenger.PCardID
AND diagnoserecord.DStatus = 1
ORDER BY DATEDIFF(diagnoserecord.DDay,diagnoserecord.FDay) DESC
-- 查询4
SELECT *
FROM train,station
WHERE train.SStationID = station.SID
AND station.CityName = '武汉'
AND train.SDate = '2020-01-22'
-- 查询5
SELECT *
FROM train,station,trainpass
WHERE train.TID = trainpass.TID
AND trainpass.SID = station.SID
AND train.SDate = '2020-01-22'
AND station.CityName = '武汉'
AND trainpass.SNo <> 1
-- 查询6
SELECT PCardID,s2.CityName,SDate
FROM taketrainrecord,station s1,station s2,train
WHERE s1.SID = taketrainrecord.SStationID
AND s2.SID = taketrainrecord.AStationID
AND taketrainrecord.TID = train.TID
AND s1.CityName = '武汉'
-- 查询7
SELECT s2.CityName,COUNT(*)
FROM taketrainrecord,station s1,station s2,train
WHERE s1.SID = taketrainrecord.SStationID
AND s2.SID = taketrainrecord.AStationID
AND taketrainrecord.TID = train.TID
AND s1.CityName = '武汉'
GROUP BY s2.CityName
-- 查询8
SELECT PCardID
FROM taketrainrecord,station,train
WHERE taketrainrecord.AStationID = station.SID
AND taketrainrecord.TID = train.TID
AND station.CityName = '武汉'
AND train.SDate >= '2020-01-01'
AND train.SDate <= '2020-01-31'
-- 查询9
SELECT DISTINCT passenger.PCardID,passenger.PName,passenger.Age,passenger.Sex,train.TName
FROM train,station,trainpass,taketrainrecord,passenger
WHERE taketrainrecord.TID = train.TID
AND taketrainrecord.PCardID = passenger.PCardID
AND train.TID = trainpass.TID
AND trainpass.SID = station.SID
AND train.SDate >= '2020-01-01'
AND train.SDate <= '2020-01-31'
AND station.CityName = '武汉'
AND taketrainrecord.PCardID NOT LIKE '420%'
-- 查询10
SELECT *
FROM train,taketrainrecord
WHERE train.TID = taketrainrecord.TID
AND (taketrainrecord.TID,taketrainrecord.CarrigeID) IN
	(SELECT DISTINCT sickview.TID,sickview.CarrigeID
	 FROM sickview)
AND train.TName = '%G007%'
AND train.SDate = '2020-01-22'
-- 查询11
SELECT s1.TID,s1.SDate,s1.CarrigeID
FROM sickview s1
WHERE 3<=(SELECT COUNT(*)
					FROM sickview s2
					WHERE s1.TID = s2.TID
					AND s1.CarrigeID = s2.CarrigeID)
-- 查询12
SELECT*
FROM sickview
WHERE sickview.PCardID NOT IN
	(SELECT traincontatcor.PCardID
	 FROM traincontatcor
	 WHERE traincontatcor.DStatus = 1)
-- 查询13
SELECT train.TName
FROM train,station
WHERE train.AStationID = station.SID
AND station.CityName IN ('北京','上海','广州')
查询14
SELECT take_1.PCardID,train_1.TName
FROM taketrainrecord take_1,train train_1,station s1,trainpass pass_1
WHERE take_1.TID = pass_1.TID
AND pass_1.SID = s1.SID
AND s1.SName = '武汉'
AND train_1.SDate = '2020-01-22'
AND EXISTS(
	SELECT *
	FROM taketrainrecord take_2,train train_2,trainpass pass_2
	WHERE take_2.TID = train_2.TID
	AND take_2.SStationID = pass_2.SID
	AND train_2.SDate = '2020-01-22'
	AND pass_2.STime > 
	)
-- 查询15
SELECT sickview.PCardID,sickview.PName,TName,sickview.SDate
FROM sickview,train
WHERE sickview.TID = train.TID
AND sickview.SDate LIKE '2020%'
-- 查询16
SELECT d1.FDay,d1.DDay,COUNT(*)
FROM diagnoserecord d1
WHERE d1.FDay IN
	(SELECT d2.FDay
	FROM diagnoserecord d2
	WHERE d1.DDay = d2.DDay)
GROUP BY d1.FDay,d1.DDay