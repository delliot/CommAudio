/*-----------------------------------------------------------------------------------------
--	SOURCE FILE:	StreamServer.cpp
--
--	PROGRAM:		CommAudio
--
--	FUNCTIONS:		StreamServe::StreamServe(QTcpSocket* tcp, QString path)
--					StreamServe::~StreamServe()
--					void StreamServe::sendFile()
--
--	DATE:			Apr. 14, 2018
--
--	REVISION:		
--
--	DESIGNER:		D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:		D. Elliot, J. Chou		
--
--	NOTES:
--	This class is used to stream (transmit) an audio file over TCP. 
--  It is initialized by the parent object (ComAudio) to handle a file streaming request
--	by a client ComAudio application. 
-----------------------------------------------------------------------------------------*/
#include "StreamServe.h"

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	StreamServe
--
--	DATE:		Apr. 14, 2018
--
--	DESIGNER:	D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:	D. Elliot, J. Chou
--
--	INTERFACE:	StreamServe::StreamServe(QTcpSocket* tcp, QString path)
--					QTcpSocket* tcp: client TCP socket
--					QString path: path & filename requested by client
--	RETURNS:
--
--	NOTES:
--	This constructor is used to initialize a StreamServe object. 
--  It takes a QTcpSocket* and QString parameter representing the filepath. 
--	
--	The QTcpSocket* passed in is created by the parent object to handle a new client 
--  client connection. The path argument contains the path and name of the file requested
--  by the client application.
-----------------------------------------------------------------------------------------*/
StreamServe::StreamServe(QTcpSocket* tcp, QString path)
	: QObject(nullptr)
	, tcp(tcp)
	, path(path)
{
}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	~StreamServe
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	
--
--	DESIGNER:	D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:	D. Elliot, J. Chou
--
--	INTERFACE:	~StreamServe()
--
--	RETURNS:
--
--	NOTES:
--	This destructor is used to destroy the StreamServe object.
-----------------------------------------------------------------------------------------*/
StreamServe::~StreamServe()
{
}

/*-----------------------------------------------------------------------------------------
--	FUNCTION:	sendFile
--
--	DATE:		Apr. 14, 2018
--
--	REVISIONS:	
--
--	DESIGNER:	D. Elliot, J. Chou, J. Lee, W. Hu
--
--	PROGRAMMER:	D. Elliot, J. Chou
--
--	INTERFACE:	
--
--	RETURNS:
--
--	NOTES:
--	This function is used to send the requested file over TCP.
--
--	Once the file has finished sending, it emits a finished signal indicating that the
--	transfer is complete.
-----------------------------------------------------------------------------------------*/
void StreamServe::sendFile()
{
	outgoing = new QFile();
	outgoing->setFileName(path);
	// Exit if outgoing File is not set to ReadOnly
	if (!outgoing->open(QIODevice::ReadOnly))
	{
		return;
	}

	// While the file reader has not hit eof
	while (!outgoing->atEnd())
	{
		QByteArray line = outgoing->readLine();
		tcp->write(line);
	}

	outgoing->close();
	emit finished();
}