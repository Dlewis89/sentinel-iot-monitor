import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class TelemetryHandler implements HttpHandler {

    @Override
    public void handle(HttpExchange httpExchange) throws IOException {
        
        switch(httpExchange.getRequestMethod()) {

            case "POST": {
                System.out.println("telemetry path is handled");

                InputStream request = httpExchange.getRequestBody();
                String data = new String(request.readAllBytes(), StandardCharsets.UTF_8);

                System.out.println(data);

                String responseStatus = "OK";
                byte[] responseBytes = responseStatus.getBytes(StandardCharsets.UTF_8);

                httpExchange.getResponseHeaders().set("Content-Type", "text/plain; charset=UTF-8");
                httpExchange.sendResponseHeaders(200, responseBytes.length);

                OutputStream response = httpExchange.getResponseBody();
                response.write(responseBytes);

                httpExchange.close();
                break;
            }

            default: {
                String responseStatus = "Method Not Allowed\n";
                byte[] responseBytes = responseStatus.getBytes(StandardCharsets.UTF_8);

                httpExchange.getResponseHeaders().set("Allow", "POST");
                httpExchange.sendResponseHeaders(405, responseBytes.length);

                httpExchange.getResponseBody().write(responseBytes);

                httpExchange.close();
            }

        }   
        
    }
        
}