USE [ZZU-DB]
GO
Create Table [ZZUExam]
(
	[ExamUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[StudentUUID] [uniqueidentifier] NOT NULL,
	[LectureUUID] [uniqueidentifier] NOT NULL,
	[Examscore] [float] NOT NULL,
	[Examnote] [float] NOT NULL,
	[Semester] [int] NOT NULL,
	[Examdatastamp] [timestamp] NOT NULL,
	Primary Key([ExamUUID]),
	foreign key([StudentUUID]) references Student([StudentUUID]) on delete cascade on update cascade,
	foreign key([LectureUUID]) references LectureinZZU([LectureUUID]) on delete cascade on update cascade
)
go