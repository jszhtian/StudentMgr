USE [ZZU-DB]
GO
CREATE TABLE [LectureMap]
(
	[ZZULectureUUID] [uniqueidentifier] Not NULL,
	[UDELectureUUID] [uniqueidentifier] Not NULL,
	Primary Key([ZZULectureUUID],[UDELectureUUID]),
	foreign key([ZZULectureUUID])references LectureinZZU(LectureUUID) on delete cascade on update cascade,
	foreign key([UDELectureUUID])references LectureinUDE(LectureUUID) on delete cascade on update cascade
)
Go