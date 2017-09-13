USE [ZZU-DB]
GO

CREATE TABLE [Student](
	[StudentUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[StudentID] [bigint] NOT NULL UNIQUE,
	[Name] [nvarchar](50) NOT NULL,
	[Birthday] [date] NOT NULL,
	[IDNumber] [bigint] NOT NULL,
	[Class] [nvarchar](50) NOT NULL,
	[Gender] [nvarchar](50) NOT NULL Check([Gender]=N'male' or [Gender]=N'female'),
	[Grade] [nvarchar](50) NOT NULL,
	[StudO] [nvarchar](50) NOT NULL,
	[MajorUUID] [uniqueidentifier] NOT NULL,
	primary key([StudentUUID]),
	foreign key([MajorUUID]) REFERENCES MajorinZZU(MajorUUID)
	ON DELETE CASCADE ON UPDATE CASCADE
)
GO


