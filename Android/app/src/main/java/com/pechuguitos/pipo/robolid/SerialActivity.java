package com.pechuguitos.pipo.robolid;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Set;

public class SerialActivity extends AppCompatActivity {
    private BluetoothAdapter mBluetoothAdapter;
    private int REQUEST_ENABLE_BT = 2;
    private ListView lista;
    private Button actualizar;
    private ArrayList<String> datos;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.serial);
        lista = findViewById(R.id.blue_list);
        lista.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                connect(((String)parent.getItemAtPosition(position)).split("\n"));
            }
        });
        actualizar = findViewById(R.id.actualizar_btn);
        actualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
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

    protected void scan() {
        Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
        datos = new ArrayList<>();
        if (pairedDevices.size() > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                datos.add(device.getName() + "\n" + device.getAddress());
            }
            Toast.makeText(this, "Seleccione un dispositivo.", Toast.LENGTH_SHORT).show();
        }
        lista.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, datos));
    }

    protected void connect(String[] info ){
        Log.d("Datos", info[0] + " " + info[1]);
    }

}
