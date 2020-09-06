CREATE TRIGGER trigger_1
	BEFORE UPDATE ON diagnoserecord
	FOR EACH ROW
	BEGIN
		IF(new.DStatus = 1) AND (old.DStatus <> 1) THEN
		INSERT INTO traincontatcor SELECT * FROM
			(SELECT tr1.SDate,t1.PCardID,1 as DS,new.PCardID as PC
				FROM taketrainrecord t1,train tr1,
				(SELECT t2.TID,t2.CarrigeID,t2.SeatRow
					AS T,C,S
					FROM taketrainrecord t2,train tr2
					WHERE t2.TID = tr2.TID
					AND DATEDIFF(new.FDay,tr2.SDate) <= 14
					AND t2.PCardID = new.PCardID
					AND t2.SStatus = 1) as tmp
				WHERE t1.TID = tr1.TID
				AND tmp.T = t1.TID
				AND tmp.C = t1.CarrigeID
				AND tmp.S-t1.SeatRow <= 1
				AND tmp.S-t1.SeatRow >= -1
				AND t1.SStatus = 1
				AND t1.PCardID <> new.PCardID) as tmp2;
			UPDATE traincontatcor SET DStatus=1 WHERE PCardID=new.PCardID;
		END IF;
		END;

CREATE TRIGGER trigger_2
	BEFORE INSERT ON diagnoserecord
	FOR EACH ROW
	BEGIN
		IF(new.DStatus = 1) THEN
		INSERT INTO traincontatcor SELECT * FROM
			(SELECT tr1.SDate,t1.PCardID,1 as DS,new.PCardID as PC
				FROM taketrainrecord t1,train tr1,
				(SELECT t2.TID,t2.CarrigeID,t2.SeatRow
					AS T,C,S
					FROM taketrainrecord t2,train tr2
					WHERE t2.TID = tr2.TID
					AND DATEDIFF(new.FDay,tr2.SDate) <= 14
					AND t2.PCardID = new.PCardID
					AND t2.SStatus = 1) as tmp
				WHERE t1.TID = tr1.TID
				AND tmp.T = t1.TID
				AND tmp.C = t1.CarrigeID
				AND tmp.S-t1.SeatRow <= 1
				AND tmp.S-t1.SeatRow >= -1
				AND t1.SStatus = 1
				AND t1.PCardID <> new.PCardID) as tmp2;
			UPDATE traincontatcor SET DStatus=1 WHERE PCardID=new.PCardID;
		END IF;
		END;

DROP TRIGGER trigger_1;
DROP TRIGGER trigger_2;

