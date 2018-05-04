package com.moppy.control.gui.mapperpanel;

import com.moppy.control.config.MoppyConfig.MIDIScriptMapperConfig;
import com.moppy.core.events.mapper.MIDIScriptMapper;
import com.moppy.core.events.mapper.scripts.ConditionScripts;
import com.moppy.core.events.mapper.scripts.DeviceAddressScripts;
import com.moppy.core.events.mapper.scripts.NoteScripts;
import com.moppy.core.events.mapper.scripts.SubAddressScripts;
import java.awt.Color;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.script.ScriptException;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JTextArea;

/**
 *
 */
public class MapperPanel extends javax.swing.JPanel {

    private final MIDIScriptMapper mapper;
    private final MapperCollectionPanel mapperPanel;
    private final MIDIScriptMapperConfig mapperConfig;

    private static final Map<String, String> CONDITION_MAP = new HashMap<>();
    private static final Map<String, String> DEVICEADDRESS_MAP = new HashMap<>();
    private static final Map<String, String> SUBADDRESS_MAP = new HashMap<>();
    private static final Map<String, String> NOTE_MAP = new HashMap<>();

    static {
        CONDITION_MAP.put(ConditionScripts.ALL_EVENTS.displayName(), ConditionScripts.ALL_EVENTS.toString());
        CONDITION_MAP.put(ConditionScripts.CHANNELS_ONE_TO_FOUR.displayName(), ConditionScripts.CHANNELS_ONE_TO_FOUR.toString());
        CONDITION_MAP.put(ConditionScripts.ONLY_SUPPORTED_NOTES.displayName(), ConditionScripts.ONLY_SUPPORTED_NOTES.toString());
        CONDITION_MAP.put("Custom", "");

        DEVICEADDRESS_MAP.put(DeviceAddressScripts.DEVICE_ONE.displayName(), DeviceAddressScripts.DEVICE_ONE.toString());
        DEVICEADDRESS_MAP.put(DeviceAddressScripts.ONE_DEVICE_PER_CHANNEL.displayName(), DeviceAddressScripts.ONE_DEVICE_PER_CHANNEL.toString());
        DEVICEADDRESS_MAP.put("Custom", "");

        SUBADDRESS_MAP.put(SubAddressScripts.SUB_ADDRESS_PER_CHANNEL.displayName(), SubAddressScripts.SUB_ADDRESS_PER_CHANNEL.toString());
        SUBADDRESS_MAP.put("Custom", "");

        NOTE_MAP.put(NoteScripts.FORCE_INTO_RANGE.displayName(), NoteScripts.FORCE_INTO_RANGE.toString());
        NOTE_MAP.put(NoteScripts.IGNORE_OUT_OF_RANGE.displayName(), NoteScripts.IGNORE_OUT_OF_RANGE.toString());
        NOTE_MAP.put(NoteScripts.STRAIGHT_THROUGH.displayName(), NoteScripts.STRAIGHT_THROUGH.toString());
        NOTE_MAP.put("Custom", "");
    }

    /**
     * Creates new form MapperPanel
     */
    public MapperPanel(MIDIScriptMapper mapper, MIDIScriptMapperConfig config, MapperCollectionPanel mapperPanel) {
        this.mapperConfig = config;
        this.mapper = mapper;
        this.mapperPanel = mapperPanel;

        initComponents();
        this.setSize(995, 250);

        conditionComboBox.setSelectedItem(mapperConfig.getConditionChoice());
        deviceAddressComboBox.setSelectedItem(mapperConfig.getDeviceAddressChoice());
        subAddressComboBox.setSelectedItem(mapperConfig.getSubAddressChoice());
        noteComboBox.setSelectedItem(mapperConfig.getNoteChoice());
    }

    public MIDIScriptMapper getMapper() {
        return mapper;
    }

    public MIDIScriptMapperConfig getMapperConfig() {
        // First update the config with the currently selected items (don't do this
        // in real-time so that programatic menu-selections don't overwrite user choices
        mapperConfig.setConditionChoice(conditionComboBox.getSelectedItem().toString());
        mapperConfig.setDeviceAddressChoice(deviceAddressComboBox.getSelectedItem().toString());
        mapperConfig.setSubAddressChoice(subAddressComboBox.getSelectedItem().toString());
        mapperConfig.setNoteChoice(noteComboBox.getSelectedItem().toString());

        return mapperConfig;
    }

    public void enableEditing(boolean enable) {
        conditionTextArea.setEditable(enable);
        conditionComboBox.setEnabled(enable);

        deviceAddressTextArea.setEditable(enable);
        deviceAddressComboBox.setEnabled(enable);

        subAddressTextArea.setEditable(enable);
        subAddressComboBox.setEnabled(enable);

        noteTextArea.setEditable(enable);
        noteComboBox.setEnabled(enable);

        deleteMapperButton.setEnabled(enable);
    }

    /**
     * This method is called from within the constructor to initialize the form. WARNING: Do NOT modify this code. The content of this method is always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        jPanel5 = new javax.swing.JPanel();
        deleteMapperButton = new javax.swing.JButton();
        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        conditionTextArea = new javax.swing.JTextArea();
        conditionComboBox = new javax.swing.JComboBox<>();
        jPanel2 = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        jScrollPane3 = new javax.swing.JScrollPane();
        deviceAddressTextArea = new javax.swing.JTextArea();
        deviceAddressComboBox = new javax.swing.JComboBox<>();
        jPanel3 = new javax.swing.JPanel();
        jLabel3 = new javax.swing.JLabel();
        jScrollPane4 = new javax.swing.JScrollPane();
        subAddressTextArea = new javax.swing.JTextArea();
        subAddressComboBox = new javax.swing.JComboBox<>();
        jPanel4 = new javax.swing.JPanel();
        jLabel4 = new javax.swing.JLabel();
        jScrollPane5 = new javax.swing.JScrollPane();
        noteTextArea = new javax.swing.JTextArea();
        noteComboBox = new javax.swing.JComboBox<>();

        setBorder(javax.swing.BorderFactory.createMatteBorder(0, 0, 1, 0, new java.awt.Color(102, 102, 102)));
        setMaximumSize(new java.awt.Dimension(32767, 165));
        setPreferredSize(new java.awt.Dimension(995, 245));
        setLayout(new java.awt.GridBagLayout());

        jPanel5.setMinimumSize(new java.awt.Dimension(0, 31));
        jPanel5.setPreferredSize(new java.awt.Dimension(992, 43));

        deleteMapperButton.setFont(deleteMapperButton.getFont().deriveFont(deleteMapperButton.getFont().getSize()+7f));
        deleteMapperButton.setText("🗑");
        deleteMapperButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                deleteMapperButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel5Layout = new javax.swing.GroupLayout(jPanel5);
        jPanel5.setLayout(jPanel5Layout);
        jPanel5Layout.setHorizontalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel5Layout.createSequentialGroup()
                .addContainerGap(937, Short.MAX_VALUE)
                .addComponent(deleteMapperButton)
                .addContainerGap())
        );
        jPanel5Layout.setVerticalGroup(
            jPanel5Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel5Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addComponent(deleteMapperButton)
                .addContainerGap(12, Short.MAX_VALUE))
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        add(jPanel5, gridBagConstraints);

        jPanel1.setPreferredSize(new java.awt.Dimension(100, 100));

        jLabel1.setText("Condition");

        conditionTextArea.setColumns(20);
        conditionTextArea.setRows(5);
        conditionTextArea.setText(mapper.getConditionScript());
        conditionTextArea.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                conditionTextAreaFocusLost(evt);
            }
        });
        jScrollPane1.setViewportView(conditionTextArea);

        conditionComboBox.setModel(new DefaultComboBoxModel(CONDITION_MAP.keySet().toArray()));
        conditionComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                conditionComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 80, Short.MAX_VALUE)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(conditionComboBox, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(conditionComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1)
                .addContainerGap())
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        add(jPanel1, gridBagConstraints);

        jLabel2.setText("Device Address");

        deviceAddressTextArea.setColumns(20);
        deviceAddressTextArea.setRows(5);
        deviceAddressTextArea.setText(mapper.getDeviceAddressScript());
        deviceAddressTextArea.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                deviceAddressTextAreaFocusLost(evt);
            }
        });
        jScrollPane3.setViewportView(deviceAddressTextArea);

        deviceAddressComboBox.setModel(new DefaultComboBoxModel(DEVICEADDRESS_MAP.keySet().toArray()));
        deviceAddressComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                deviceAddressComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane3, javax.swing.GroupLayout.DEFAULT_SIZE, 405, Short.MAX_VALUE)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(jLabel2)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(deviceAddressComboBox, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(deviceAddressComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane3)
                .addContainerGap())
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        add(jPanel2, gridBagConstraints);

        jLabel3.setText("Sub Address");

        subAddressTextArea.setColumns(20);
        subAddressTextArea.setRows(5);
        subAddressTextArea.setText(mapper.getSubAddressScript());
        subAddressTextArea.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                subAddressTextAreaFocusLost(evt);
            }
        });
        jScrollPane4.setViewportView(subAddressTextArea);

        subAddressComboBox.setModel(new DefaultComboBoxModel(SUBADDRESS_MAP.keySet().toArray()));
        subAddressComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                subAddressComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel3Layout = new javax.swing.GroupLayout(jPanel3);
        jPanel3.setLayout(jPanel3Layout);
        jPanel3Layout.setHorizontalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane4, javax.swing.GroupLayout.DEFAULT_SIZE, 245, Short.MAX_VALUE)
                    .addGroup(jPanel3Layout.createSequentialGroup()
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(subAddressComboBox, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jPanel3Layout.setVerticalGroup(
            jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel3Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addGroup(jPanel3Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel3)
                    .addComponent(subAddressComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane4)
                .addContainerGap())
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        add(jPanel3, gridBagConstraints);

        jLabel4.setText("Note");

        noteTextArea.setColumns(20);
        noteTextArea.setRows(5);
        noteTextArea.setText(mapper.getNoteScript());
        noteTextArea.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                noteTextAreaFocusLost(evt);
            }
        });
        jScrollPane5.setViewportView(noteTextArea);

        noteComboBox.setModel(new DefaultComboBoxModel(NOTE_MAP.keySet().toArray()));
        noteComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                noteComboBoxActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel4Layout = new javax.swing.GroupLayout(jPanel4);
        jPanel4.setLayout(jPanel4Layout);
        jPanel4Layout.setHorizontalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel4Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane5, javax.swing.GroupLayout.DEFAULT_SIZE, 182, Short.MAX_VALUE)
                    .addGroup(jPanel4Layout.createSequentialGroup()
                        .addComponent(jLabel4)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(noteComboBox, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addContainerGap())
        );
        jPanel4Layout.setVerticalGroup(
            jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel4Layout.createSequentialGroup()
                .addGap(0, 0, 0)
                .addGroup(jPanel4Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel4)
                    .addComponent(noteComboBox, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(4, 4, 4)
                .addComponent(jScrollPane5)
                .addContainerGap())
        );

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        add(jPanel4, gridBagConstraints);
    }// </editor-fold>//GEN-END:initComponents

    private void deleteMapperButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_deleteMapperButtonActionPerformed
      mapperPanel.removeMapper(this);
    }//GEN-LAST:event_deleteMapperButtonActionPerformed

    private void conditionTextAreaFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_conditionTextAreaFocusLost
        try {
            mapper.setConditionScript(conditionTextArea.getText());
            mapperConfig.setConditionCustomScript(conditionTextArea.getText());
            conditionTextArea.setForeground(Color.BLACK);
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            conditionTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_conditionTextAreaFocusLost

    private void deviceAddressTextAreaFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_deviceAddressTextAreaFocusLost
        try {
            mapper.setDeviceAddressScript(deviceAddressTextArea.getText());
            mapperConfig.setDeviceAddressCustomScript(deviceAddressTextArea.getText());
            deviceAddressTextArea.setForeground(Color.BLACK);
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            deviceAddressTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_deviceAddressTextAreaFocusLost

    private void subAddressTextAreaFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_subAddressTextAreaFocusLost
        try {
            mapper.setSubAddressScript(subAddressTextArea.getText());
            mapperConfig.setSubAddressCustomScript(subAddressTextArea.getText());
            subAddressTextArea.setForeground(Color.BLACK);
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            subAddressTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_subAddressTextAreaFocusLost

    private void noteTextAreaFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_noteTextAreaFocusLost
        try {
            mapper.setNoteScript(noteTextArea.getText());
            mapperConfig.setNoteCustomScript(noteTextArea.getText());
            noteTextArea.setForeground(Color.BLACK);
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            noteTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_noteTextAreaFocusLost

    private void setTextAreaEditable(JTextArea textArea, boolean enabled) {
        textArea.setEditable(enabled);
        textArea.setBackground(enabled ? Color.WHITE : Color.LIGHT_GRAY);
    }

    private void conditionComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_conditionComboBoxActionPerformed
        if (conditionComboBox.getSelectedItem().equals("Custom")) {
            conditionTextArea.setText(mapperConfig.getConditionCustomScript());
            setTextAreaEditable(conditionTextArea, true);
        } else {
            setTextAreaEditable(conditionTextArea, false);
            conditionTextArea.setText(CONDITION_MAP.get(conditionComboBox.getSelectedItem().toString()));
        }
        try {
            mapper.setConditionScript(conditionTextArea.getText());
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            noteTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_conditionComboBoxActionPerformed

    private void deviceAddressComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_deviceAddressComboBoxActionPerformed
        if (deviceAddressComboBox.getSelectedItem().equals("Custom")) {
            deviceAddressTextArea.setText(mapperConfig.getDeviceAddressCustomScript());
            setTextAreaEditable(deviceAddressTextArea, true);
        } else {
            setTextAreaEditable(deviceAddressTextArea, false);
            deviceAddressTextArea.setText(DEVICEADDRESS_MAP.get(deviceAddressComboBox.getSelectedItem().toString()));
        }
        try {
            mapper.setDeviceAddressScript(deviceAddressTextArea.getText());
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            noteTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_deviceAddressComboBoxActionPerformed

    private void subAddressComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_subAddressComboBoxActionPerformed
        if (subAddressComboBox.getSelectedItem().equals("Custom")) {
            subAddressTextArea.setText(mapperConfig.getSubAddressCustomScript());
            setTextAreaEditable(subAddressTextArea, true);
        } else {
            setTextAreaEditable(subAddressTextArea, false);
            subAddressTextArea.setText(SUBADDRESS_MAP.get(subAddressComboBox.getSelectedItem().toString()));
        }
        try {
            mapper.setSubAddressScript(subAddressTextArea.getText());
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            noteTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_subAddressComboBoxActionPerformed

    private void noteComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_noteComboBoxActionPerformed
        if (noteComboBox.getSelectedItem().equals("Custom")) {
            noteTextArea.setText(mapperConfig.getNoteCustomScript());
            setTextAreaEditable(noteTextArea, true);
        } else {
            setTextAreaEditable(noteTextArea, false);
            noteTextArea.setText(NOTE_MAP.get(noteComboBox.getSelectedItem().toString()));
        }
        try {
            mapper.setNoteScript(noteTextArea.getText());
        } catch (ScriptException ex) {
            Logger.getLogger(MapperPanel.class.getName()).log(Level.WARNING, null, ex);
            noteTextArea.setForeground(Color.RED);
        }
    }//GEN-LAST:event_noteComboBoxActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JComboBox<String> conditionComboBox;
    private javax.swing.JTextArea conditionTextArea;
    private javax.swing.JButton deleteMapperButton;
    private javax.swing.JComboBox<String> deviceAddressComboBox;
    private javax.swing.JTextArea deviceAddressTextArea;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel4;
    private javax.swing.JPanel jPanel5;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JScrollPane jScrollPane5;
    private javax.swing.JComboBox<String> noteComboBox;
    private javax.swing.JTextArea noteTextArea;
    private javax.swing.JComboBox<String> subAddressComboBox;
    private javax.swing.JTextArea subAddressTextArea;
    // End of variables declaration//GEN-END:variables
}
