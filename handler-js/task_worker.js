import { parentPort } from 'worker_threads';

const workerStatusEnum = {
  INITIALIZING: 'initializing',
  RUNNING: 'running',
  ERROR: 'error',
  COMPLETE: 'complete',
};

let workerStatus = workerStatusEnum.INITIALIZING;
let inputData = null;
let moduleRunner = null;

const useStudyGeneratorRunner = () => {
  return {
    Run: async () => {
      console.log(">>>>>> [task_worker] running study generator...");
      workerStatus = workerStatusEnum.RUNNING;
    }
  }
}

const createModuleRunner = (module_name) => {
  switch (module_name) {
    case 'study-generator':
      return useStudyGeneratorRunner();
    default:
      throw new Error(`[task_worker] unknown module name: ${module_name}`);
  }
};

parentPort.on('message', async (message) => {
  if (!message.type) {
    throw new Error('[task_worker] missing message type in message');
  }

  switch (message.type) {
    case 'status':
      console.log(">>>>>> [task_worker] message from parent: status query ");
      break;
    case 'input':
      console.log(">>>>>> [task_worker] input data: ", message.data);
      inputData = message.data;
      moduleRunner = createModuleRunner(inputData.module_name);
      moduleRunner.Run();
      break;
    default:
      console.log(">>>>>> [task_worker] unknown message type: ", message.type);
  }



  parentPort.postMessage({
    type: 'status',
    data: 'success',
  });
});