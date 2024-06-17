import useGatewayHelpers from './gateway_helpers.js';
import { Worker } from 'worker_threads';

const numberOfWorkers = 2;

async function RunHandler() {
  console.log("[AVRP-Handler]: Starting handler...");
  console.log("[AVRP-Handler]: authenticating to gateway server...");
  const { 
    getHandlerTasks 
  } = await useGatewayHelpers("http://localhost:6060", "avrpdev", "avrp@dev");

  console.log("[AVRP-Handler]: Starting timer...");

  const onTimerTick = async () => {
    console.log("[AVRP-Handler]: Timer tick");
    console.log("-- checking handler tasks...");
    const handlerTasks = await getHandlerTasks();
    console.log("-- handler tasks: ", handlerTasks);

    handlerTasks.handler_tasks.forEach((task, index) => {
      const worker = new Worker('./handler-js/task_worker.js');
      worker.postMessage({
        type: 'input',
        data: task,
      });

      worker.on('message', (message) => {
        console.log("---- [AVRP-Handler] worker message: ", message);
      });

      worker.on('error', (error) => {
        console.error("---- [AVRP-Handler] worker error: ", error);
      });

      worker.on('exit', (code) => {
        if (code !== 0) {
          console.error(`---- [AVRP-Handler] Worker stopped with exit code ${code}`);
        }
      });
    })
  }

  onTimerTick(); // immediately execute on first run

  setInterval(onTimerTick, 10000);
}

export {
  RunHandler,
}