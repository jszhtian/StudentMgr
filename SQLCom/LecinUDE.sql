USE [ZZU-DB]
GO
CREATE TABLE [LectureinUDE]
(
	[LectureUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[LectureName] [nvarchar](50) NOT NULL,
	[Module] [int] NOT NULL,
	[Semester] [int] NOT NULL,	
	[EACTSCredit] [float] NOT NULL,
	[Teachinghours] [int] NOT NULL,
Primary Key([LectureUUID])
)
Go