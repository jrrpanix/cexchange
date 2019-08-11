"use strict";
exports.__esModule = true;
var WebSocket = require("ws");
var typescript_logging_1 = require("typescript-logging");
var express = require("express");
var bodyParser = require("body-parser");
var Program = /** @class */ (function () {
    function Program(_args) {
        this.wsData = 0;
        this.logger = this.createLogger('simple-ws-server', []);
        this.initWebServer();
        this.initTimer();
    }
    Program.prototype.createLogger = function (_name, _params) {
        var options = new typescript_logging_1.LoggerFactoryOptions();
        options.addLogGroupRule(new typescript_logging_1.LogGroupRule(new RegExp("app" + ".+"), typescript_logging_1.LogLevel.Info));
        var factory = typescript_logging_1.LFService.createNamedLoggerFactory("app", options);
        return factory.getLogger("app.default");
    };
    Program.prototype.initWebServer = function () {
        this.express = express();
        this.router = express.Router();
        // Add some middleware to support CORS requests
        this.express
            .use(function (_req, resp, next) {
            resp.header("Access-Control-Allow-Origin", "*");
            resp.header("Access-Control-Allow-Methods", "GET, HEAD, POST, PATCH, PUT, DELETE, OPTIONS");
            resp.header("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Access-Control-Allow-Headers, Origin, Accept, X-Requested-With, Content-Type, Access-Control-Request-Method, Access-Control-Request-Headers");
            next();
        });
        this.express
            .use(bodyParser.json()) // support json encoded bodies
            .use(bodyParser.urlencoded({ extended: true })) // support encoded bodies
            .use("/testws", this.router);
        this.router.get('/', function (req, resp) {
            resp.status(200).json({ message: "Hello GCLiquid customers" });
        });
    };
    Program.prototype.initTimer = function () {
        var _this = this;
        var interval = 1 * 1000;
        this.wsTimer = setInterval(function () {
            var args = [];
            for (var _i = 0; _i < arguments.length; _i++) {
                args[_i] = arguments[_i];
            }
            if (_this.websocket) {
                var data_1 = JSON.stringify({ symbol: 'MSFT', price: _this.wsData++ });
                _this.websocket.clients.forEach(function (client) {
                    if (client.readyState === WebSocket.OPEN) {
                        client.send(data_1);
                    }
                });
            }
        }, interval);
    };
    Program.prototype.initWebSocketWS = function (httpServer) {
        var _this = this;
        if (this.websocket) {
            return;
        }
        // ws://localhost:3000/testws/quotes
        this.websocket = new WebSocket.Server({ server: httpServer, path: '/testws/quotes' });
        this.websocket.on('connection', function (socket) {
            _this.logger.info('A client connected through the socket');
            socket.on('message', function (event) {
                _this.logger.info('A client sent a message to the socket:');
                _this.logger.info("[" + event.toString() + "]");
            });
            socket.on('close', function (_event) {
                _this.logger.info('A client disconnected from the socket');
            });
            socket.on('error', function (event) {
                _this.logger.error("WebSocket error: " + event.message);
            });
            // Here we can put in event handlers for messages that the clients send us...
        });
    };
    Program.prototype.messageLoop = function () {
        var _this = this;
        var http = require('http').Server(this.express);
        var port = 3000;
        var httpServer = http.listen(port, function () {
            _this.logger.info("TestWS listening on port " + port + "!");
        });
        // this.initWebSocket(http);
        this.initWebSocketWS(httpServer);
    };
    return Program;
}());
exports.Program = Program;
var program = new Program(process.argv);
program.messageLoop();
