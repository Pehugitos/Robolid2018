package com.pechuguitos.pipo.robolid;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.AsyncTask;
import android.util.Log;

import java.io.IOException;
import java.util.UUID;

public class ConnectBT extends AsyncTask<BluetoothDevice, Void, BluetoothSocket> {
    @Override
    protected BluetoothSocket doInBackground(BluetoothDevice... bluetoothDevice) {
        Log.d("Datos", bluetoothDevice[0].getName() + " " + bluetoothDevice[0].getAddress());
        UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
        BluetoothSocket mSocket;

        try {
            mSocket = bluetoothDevice[0].createInsecureRfcommSocketToServiceRecord(uuid);
            mSocket.connect();
            return mSocket;
        } catch (IOException ioe) {
            Log.e("app>", "Desde Dentro" + ioe);
            return null;

        }
    }

    @Override
    protected void onPostExecute(BluetoothSocket result) {
        if(result == null){
            cancel(true);
        }
    }

}
