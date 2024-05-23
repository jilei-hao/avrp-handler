import FormData from 'form-data';
import fs from 'fs';

export default async function useDSHelpers(url) {
  const uploadData = async (cachedFilePath, dsFolder, dsFilename) => {
    console.log("[useDSHelpers::uploadData] folder: ", dsFolder, " filename: ", dsFilename);

    const formData = new FormData();

    formData.append('file', fs.createReadStream(cachedFilePath));
    formData.append('folder', dsFolder);
    formData.append('filename', dsFilename);
    formData.append('create_folder_if_not_exists', 'true');

    return fetch(`${url}/data`, {
      method: 'POST',
      body: formData
    }).then((res) => {
      if (!res.ok) {
        throw new Error('[useDSHelpers::uploadData]: Error uploading data!');
      }
      return res.json();
    }).then((data) => {
      return data.fileId;
    }).catch((error) => {
      console.error(`[useDSHelpers::uploadData] Error connecting to the server: ${error}`);
    });
  };
}