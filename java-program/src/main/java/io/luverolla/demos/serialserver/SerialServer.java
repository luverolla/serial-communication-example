package io.luverolla.demos.serialserver;

import java.io.*;
import java.util.*;

import purejavacomm.*;

public class SerialServer implements Runnable, SerialPortEventListener
{
    static CommPortIdentifier portId;
    static Enumeration portList;

    InputStream inputStream;
    SerialPort serialPort;
    Thread readThread;

    public static void main(String[] args)
    {
        portList = CommPortIdentifier.getPortIdentifiers();

        while(portList.hasMoreElements())
        {
            portId = (CommPortIdentifier) portList.nextElement();
            if(portId.getPortType() == CommPortIdentifier.PORT_SERIAL)
            {
                // if(portId.getName().equals("/dev/term/a"))
                if (portId.getName().equals("COM7"))
                {
                    SerialServer reader = new SerialServer();
                }
            }
        }
    }

    public SerialServer()
    {
        try {
            serialPort = (SerialPort) portId.open("SerialServerApp", 2000);
        }
        catch (PortInUseException e) {
            System.out.println(e);
        }
        
        try {
            inputStream = serialPort.getInputStream();
        }
        catch (IOException e) {
            System.out.println(e);
        }
        
	try {
            serialPort.addEventListener(this);
	}
        catch (TooManyListenersException e) {
            System.out.println(e);
        }
        
        serialPort.notifyOnDataAvailable(true);
        
        try {
            serialPort.setSerialPortParams(38400,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
        }
        catch (UnsupportedCommOperationException e) {
            System.out.println(e);
        }
        
        readThread = new Thread(this);
        readThread.start();
    }

    @Override
    public void run()
    {
        try {
            Thread.sleep(20000);
        }
        catch (InterruptedException e) {
            System.out.println(e);
        }
    }

    @Override
    public void serialEvent(SerialPortEvent event)
    {
        switch(event.getEventType())
        {
            case SerialPortEvent.BI,
                 SerialPortEvent.OE,
                 SerialPortEvent.FE,
                 SerialPortEvent.PE,
                 SerialPortEvent.CD,
                 SerialPortEvent.CTS,
                 SerialPortEvent.DSR,
                 SerialPortEvent.RI,
                 SerialPortEvent.OUTPUT_BUFFER_EMPTY -> {}
             
            case SerialPortEvent.DATA_AVAILABLE ->
            {
                byte[] readBuffer = new byte[16];

                try {
                    while (inputStream.available() > 0)
                    {
                        inputStream.readNBytes(readBuffer, 0, 16);
                        System.out.print(new String(readBuffer));
                    }
                }
                catch (IOException e) {
                    System.out.println(e);
                }
            }
        }
    }
}