USE [ZZU-DB]
GO
CREATE TABLE [ZZULectureSelect]
(
	[MajorUUID] [uniqueidentifier] Not NULL,
	[LectureUUID] [uniqueidentifier] Not NULL,
	Primary Key([MajorUUID],[LectureUUID]),
	foreign key([MajorUUID])references MajorinZZU(MajorUUID) on delete cascade on update cascade,
	foreign key([LectureUUID])references LectureinZZU(LectureUUID) on delete cascade on update cascade
)
go