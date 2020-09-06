SET SCHEMA ems;
create table Station(
	SID int,
	SName char(20),
	CityName char(30),
	primary key (SID)
	);
create table Train(
	TID int,
	SDate date,
	TName char(20),
	SStationID int,
	AStationID int,
	STime time,
	ATime time,
	primary key (TID),
	unique (SDate,TName),
	foreign key (SStationID) references Station(SID),
	foreign key (AStationID) references Station(SID)
	);
create table TrainPass(
	TID int,
	SNo smallint,
	SID int,
	STime time,
	ATime time,
	primary key (TID,SNo),
	foreign key (TID) references Train(TID),
	foreign key (SID) references Station(SID)
	);
create table Passenger(
	PCardID char(18),
	PName char(20),
	Sex bit,
	Age smallint,
	primary key (PCardID)
	);
create table TakeTrainRecord(
	RID int,
	PCardID char(18),
	TID int,
	SStationID int,
	AStationID int,
	CarrigeID smallint,
	SeatRow smallint,
	SeatNo char(1),
	SStatus int,
	primary key (RID),
	foreign key (PCardID) references Passenger(PCardID),
	foreign key (TID) references Train(TID),
	foreign key (SStationID) references Station(SID),
	foreign key (AStationID) references Station(SID),
	constraint c1 check (SeatNo in ('A','B','C','E','F')),
	constraint c2 check (SStatus in (0,1,2))
	);
create table DiagnoseRecord(
	DID int,
	PCardID char(18),
	DDay date,
	DStatus smallint,
	FDay date,
	primary key (DID),
	foreign key (PCardID) references Passenger(PCardID),
	constraint c3 check (Dstatus in (1,2,3))
	);
	CREATE TABLE TrainContatcor(
	CDate date,
	CCardID char(18),
	DStatus smallint,
	PCardID char(18),
	primary key (CDate,CCardID,DStatus,PCardID),
	foreign key (CCardID) references Passenger(PCardID),
	foreign key (PCardID) references Passenger(PCardID));
	
	//创建一个新冠确诊病人的乘火车记录视图
	
	CREATE VIEW SickView(PCardID,PName,Age,TID,SDate,CarrigeID,SeatRow,SeatNo)
	AS
	SELECT passenger.PCardID,passenger.PName,passenger.Age,taketrainrecord.TID,SDate,CarrigeID,SeatRow,SeatNo 
	FROM taketrainrecord,diagnoserecord,passenger,train
	WHERE diagnoserecord.PCardID = taketrainrecord.PCardID AND diagnoserecord.PCardID = passenger.PCardID
	AND taketrainrecord.TID = train.TID
	AND diagnoserecord.DStatus = 1
	AND taketrainrecord.SStatus = 1
	ORDER BY passenger.PCardID,SDate DESC
	
	//创建一个表存储乘车记录表中的从武汉出发的乘客的乘车记录
	create table WH_TakeTrainRecord(
	RID int,
	PCardID char(18),
	TID int,
	SStationID int,
	AStationID int,
	CarrigeID smallint,
	SeatRow smallint,
	SeatNo char(1),
	SStatus int,
	primary key (RID),
	foreign key (PCardID) references Passenger(PCardID),
	foreign key (TID) references Train(TID),
	foreign key (SStationID) references Station(SID),
	foreign key (AStationID) references Station(SID),
	constraint c4 check (SeatNo in ('A','B','C','E','F')),
	constraint c5 check (SStatus in (0,1,2))
	);


INSERT INTO WH_TakeTrainRecord
	SELECT *
	FROM taketrainrecord
	WHERE TID IN
		(SELECT TID
		 FROM train,station
		 WHERE train.SStationID = station.SID AND station.SName = '武汉')
		 
 
	