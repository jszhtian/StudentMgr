USE [ZZU-DB]
GO
Create Table [SelectionExam]
(
	[ExamUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[StudentUUID] [uniqueidentifier] NOT NULL,
	[Examscore] [float] NOT NULL,
	[type] [nvarchar](50) NOT NULL,
	[Examdatestamp] [datestamp] NOT NULL,
	Primary Key([ExamUUID]),
	foreign key([StudentUUID]) references Student([StudentUUID]) on delete cascade on update cascade
)
Go