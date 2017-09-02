USE [ZZU-DB]
GO
CREATE TABLE [MajorinZZU](
	[MajorUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[MajorName] [nvarchar](50) NOT NULL,
	[Supervisor] [nvarchar](50) NOT NULL,
	[MajorinUDE] [uniqueidentifier] NOT NULL,
	Primary Key([MajorUUID]),
	foreign key([MajorinUDE]) REFERENCES MajorinUDE(MajorUUID)
	ON DELETE CASCADE ON UPDATE CASCADE
)
Go