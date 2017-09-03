USE [ZZU-DB]
GO
CREATE TABLE [LectureinZZU]
(
	[LectureUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[LectureName] [nvarchar](50) NOT NULL Unique,
	[Type] [nvarchar](50) NOT NULL,
	[Module] [int] NOT NULL,	
	[CreditinUDE] [float] NOT NULL,
	[Teachinghours] [int] NOT NULL,
Primary Key([LectureUUID])
)
Go