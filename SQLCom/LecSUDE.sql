USE [ZZU-DB]
GO
CREATE TABLE [UDELectureSelect]
(
	[MajorUUID] [uniqueidentifier] Not NULL,
	[LectureUUID] [uniqueidentifier] Not NULL,
	Primary Key([MajorUUID],[LectureUUID]),
	foreign key([MajorUUID])references MajorinUDE(MajorUUID) on delete cascade on update cascade,
	foreign key([LectureUUID])references LectureinUDE(LectureUUID) on delete cascade on update cascade
)
go