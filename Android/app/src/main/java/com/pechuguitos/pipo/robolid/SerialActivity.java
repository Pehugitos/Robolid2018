package com.pechuguitos.pipo.robolid;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.ExecutionException;


public class SerialActivity extends AppCompatActivity {
    private BluetoothAdapter mBluetoothAdapter;
    private int REQUEST_ENABLE_BT = 2;
    private ListView lista;
    private Button actualizar;
    private List<BluetoothDevice> pairedDevices;
    private BluetoothSocket mSocket;
    private OutputStream stream;
    private SeekBar left, right;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.serial);
        lista = findViewById(R.id.blue_list);
        lista.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                connect(pairedDevices.get(position));
            }
        });
        left = (SeekBar) findViewById(R.id.seekBarL);
        right = (SeekBar) findViewById(R.id.seekBarR);
        left.setProgress(156);
        left.refreshDrawableState();
        right.setProgress(156);
        right.refreshDrawableState();

        left.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (progress % 12 == 0){
                    mandarDatoL(progress);}
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(156);
                seekBar.refreshDrawableState();
            }
        });

        right.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (progress % 12 == 0){
                    mandarDatoR(progress);}
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                seekBar.setProgress(156);
                seekBar.refreshDrawableState();
            }
        });


        actualizar = findViewById(R.id.actualizar_btn);
        actualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                /*lista.setVisibility(View.GONE);
                actualizar.setVisibility(View.GONE);
                findViewById(R.id.sliders).setVisibility(View.VISIBLE);*/
                scan();

            }
        });

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        } else
            scan();
    }

    private void mandarDatoL(int dato) {
        try {
            Log.d("Left", "L" + dato);
            stream.write(("L" + dato).getBytes());
            stream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void mandarDatoR(int dato) {
        try {
            Log.d("Right", "R" + dato);
            stream.write(("R" + dato).getBytes());
            stream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void scan() {
        pairedDevices = new ArrayList<BluetoothDevice>();
        pairedDevices.addAll(mBluetoothAdapter.getBondedDevices());
        ArrayList<String> datos = new ArrayList<>();
        if (pairedDevices.size() > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                datos.add(device.getName() + "\n" + device.getAddress());
            }
            Toast.makeText(this, "Seleccione un dispositivo.", Toast.LENGTH_SHORT).show();
        }
        lista.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, datos));
    }

    protected void escribe() {
        try {
            stream.write("B".getBytes());
            stream.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    protected void connect(BluetoothDevice info) {
        try {
            mSocket = new ConnectBT().execute(info).get();
            stream = mSocket.getOutputStream();
            escribe();
            lista.setVisibility(View.GONE);
            actualizar.setVisibility(View.GONE);
            findViewById(R.id.sliders).setVisibility(View.VISIBLE);
        } catch (InterruptedException e) {
            Log.e("app>", "Desde Fuera" + e);
        } catch (ExecutionException e) {
            Log.e("app>", "Desde Fuera" + e);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
