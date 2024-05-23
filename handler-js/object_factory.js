export default function useObjectFactory() {
  const createModuleDataHeader = (moduleName, studyId, moduleOutputArray) => {
    return {
      moduleName: moduleName,
      studyId: studyId,
      moduleOutputs: moduleOutputArray
    };
  };

  const createModuleOutput = (outputName, tpData) => {
    return {
      outputName: outputName,
      timePointData: tpData
    };
  };

  const createTPData = (timePoint, primary_index, secondary_index, dsId) => {
    return {
      timePoint: timePoint,
      primaryIndex: primary_index,
      secondaryIndex: secondary_index,
      dsId: dsId
    };
  };

  const createModuleDataFileInfo = (moduleName, studyId, moduleOutputName, timePoint, 
    primaryIndex, secondaryIndex, filePath) => {
    return {
      moduleName: moduleName,
      studyId: studyId,
      moduleOutputName: moduleOutputName,
      timePoint: timePoint,
      primaryIndex: primaryIndex,
      secondaryIndex: secondaryIndex,
      filePath: filePath
    };
  };

  return {
    createModuleDataHeader,
    createModuleOutput,
    createTPData,
    createModuleDataFileInfo,
  }
}