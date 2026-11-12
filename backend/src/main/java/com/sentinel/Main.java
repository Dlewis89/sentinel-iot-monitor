package com.sentinel;

import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.net.InetSocketAddress;

public class Main {
    public static void main(String[] args) {
        System.out.println("Sentinel backend starting...");

        try {
            InetSocketAddress socket = new InetSocketAddress(8080);
            HttpServer httpServer = HttpServer.create(socket, 0);

            httpServer.createContext("/telemetry", new TelemetryHandler());
            
            httpServer.start();

            System.out.println("Sentinel backend started.");
        } catch (IOException e) {
            System.err.println("Failed to start Sentinel server: " + e.getMessage());
        }
    }
}

